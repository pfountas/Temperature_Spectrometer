/*
 * TempScope.h
 *
 *  Created on: Dec 3, 2014
 *      Author: pfountas
 */
#ifndef TEMPSCOPE_TEMPSCOPE_H_
#define TEMPSCOPE_TEMPSCOPE_H_

#include "mbed.h"
#include "rtos.h"
#include "TMP102.h"
#include "dsp.h"

class TempScope {
public:
	TempScope(TMP102 *device);
	~TempScope();

	void setAqcuisitionFrequencyInHz(int f);

	void setNumberOfSamples(int n);

	void enable();

	void disable();

	void getSignal(const std::vector<float>& _retvalue);

	void getSignalDFT(const std::vector<complex_t>& _retvalue);

	void getSignalSpectrum(const std::vector<float>& _retvalue);

	void getSignalPSD(const std::vector<float>& _retvalue);

private:

	void dftThreadOperation(void const *args);

	void daq();

	int daqfreq = 1; // Hz

	int nsamples = 64; // samples

	int currentSample = 0; // in DFT bucket

	TMP102 *sensor;

	Ticker daqtimer;

	std::vector<float> *signal;

	std::vector<complex_t> *signalDFT;

	std::vector<float> *signalSpectrum;

	std::vector<float> *signalPSD;

	Mutex *dftUpdateMutex;

	Thread *dftComputeThread;

};

#endif /* TEMPSCOPE_TEMPSCOPE_H_ */
