/*
 * TempScope.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: pfountas
 */

#include "TempScope.h"

#define COMPUTE_DFT_SIG 0x10001001 // (random value)

using namespace std;

TempScope::TempScope(TMP102 *device)
{
	this->sensor = device;
	this->signal =
			new std::vector<float>(this->nsamples);
	this->signalDFT =
			new std::vector<complex_t>(this->nsamples);
	this->signalSpectrum =
			new std::vector<float>(this->nsamples);
	this->signalPSD =
			new std::vector<float>(this->nsamples);
	this->dftComputeThread =
			new Thread(this->dft);
	this->dftUpdateMutex =
			new Mutex();
}

TempScope::~TempScope()
{
	delete this->sensor;
	delete this->signal;
	delete this->signalDFT;
	delete this->signalSpectrum;
	delete this->signalPSD;
	delete this->dftComputeThread;
	delete this->dftUpdateMutex;
}

void TempScope::setAqcuisitionFrequencyInHz(int f)
{
	if (f > 0)
		this->daqfreq = f;
}

void TempScope::setNumberOfSamples(int n)
{
	if (floor(n) > 0)
		this->nsamples = floor(n);
}

void enable()
{
	daqtimer.attach(&this->daq, 1/this->daqfreq);
}

void disable()
{
	daqtimer.detach();
}

void TempScope::getSignal(const vector<float>& _retvalue)
{
	int N = this->nsamples;
	this->dftUpdateMutex->lock();
	_retvalue.vector<float>(this->signal,
			N+sizeof(this->signal)/sizeof(float));
	this->dftUpdateMutex->unlock();
}

void TempScope::getSignalDFT(const vector<complex_t>& _retvalue)
{
	int N = this->nsamples;
	this->dftUpdateMutex->lock();
	_retvalue.vector<complex_t>(this->signalDFT,
			N+sizeof(this->signalDFT)/sizeof(complex_t));
	this->dftUpdateMutex->unlock();
}

void TempScope::getSignalSpectrum(const vector<float>& _retvalue)
{
	int N = this->nsamples;
	this->dftUpdateMutex->lock();
	_retvalue.vector<float>(this->signalSpectrum,
			N+sizeof(this->signalSpectrum)/sizeof(float));
	this->dftUpdateMutex->unlock();
}

void TempScope::getSignalPSD(const vector<float>& _retvalue)
{
	int N = this->nsamples;
	this->dftUpdateMutex->lock();
	_retvalue.vector<float>(this->signalPSD,
			N+sizeof(this->signalPSD)/sizeof(float));
	this->dftUpdateMutex->unlock();
}

void TempScope::dftThreadOperation(void const *args)
{
	while (true) {

		Thread::signal_wait(COMPUTE_DFT_SIG); // wait to be signaled

		int N = this->nsamples;

		// convert signal to complex
		for (int n = 0; n < N; n++) cx[n] = complex_num(x[n], 0);

		// init DFT output sequence
		complex_t *X = malloc(N*sizeof(complet_x));
		for (int n = 0; n < N; n++) X[n] = complex_num(0, 0); // init to 0

		// compute DFT
		dft(X, cx, N);

		// remove DC component and AC alliases, and spread the rest of the signal
		complex_t *spectrum = malloc(N*sizeof(complet_x));
		for (int n = 0; n < N; n++)
			spectrum[n] = 0;
		for (int n = 0; n < floor(N / 2) - 1; n++) {
			spectrum[2 * n] = complex_norm(X[n + 1]);
			spectrum[2 * n + 1] =
					(complex_norm(X[n + 2]) + complex_norm(X[n + 1])) / 2;
		}

		// estimate Power Spectral Density (PSD)
		complex_t *Pxx = malloc(N*sizeof(complet_x));
		for (int n = 0; n < N; n++) Pxx[n] = 0; // init to 0
		for (int n = 0; n < floor(N / 2) - 1; n++) {
			Pxx[2 * n] = 20 * log10(pow(complex_norm(X[n + 1]), 2));
			float avg = (complex_norm(X[n + 2]) + complex_norm(X[n + 1])) / 2;
			Pxx[2 * n + 1] = 20 * log10(pow(avg, 2));
		}


		// store X, spectrum, Pxx
		this->dftUpdateMutex->lock(); // RAW (Read-After-Write)
		for (int i = 0; i < N; i++) {
			this->signalDFT->push_back(X[i]);
			this->signalSpectrum->push_back(spectrum[i]);
			this->signalPSD->push_back(Pxx[i]);
		}
		this->dftUpdateMutex->unlock();

		free(X); // release DFT output sequence
		free(spectrum); // release spectrum temp
		free(Pxx); // release PSD temp
	}
}

void TempScope::daq()
{
	float temp = 0;
	sensor->temp(&temp); // get temperature
	this->signal->push_back(temp);
	mod(++this->currSample,this->nsamples);
	if (!this->currSample) {
		// run DFT computation thread
		this->dftComputeThread->signal_set(COMPUTE_DFT_SIG);
	}
}
