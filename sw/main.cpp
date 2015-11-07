#include "mbed.h"
#include "rtos.h"
#include "N5110.h"
#include "TMP102.h"
#include "dsp.h"

// On-boards LEDs for visual feedback
BusOut leds(LED4, LED3, LED2, LED1);

// Local filesystem
LocalFileSystem local("local");
FILE *fp = NULL;

// On-board controls
DigitalIn a_btn(p16, PullUp);
DigitalIn b_btn(p17, PullUp);
DigitalIn sw(p18);

// Serial connection
Serial serial(USBTX, USBRX);
#define getc(c) 	serial.getc(c)
#define printf(...) serial.printf( __VA_ARGS__ )

// Temperature sensor
TMP102 tmp(0x48, p28, p27); // I2C Temperature sensor
bool enable = 0;
bool isLoggingOn = 0;

// LCD display
N5110 display(p7, p8, p9, p10, p11, p13, p21); // LCD 84x48
#define DISP_WIDTH 	84
#define DISP_HEIGHT 48
bool dirty; // screen redraw flag

// DFT
#define N  64 	// samples
#define Fs 1000 // Sampling frequency
float x[N];        // signal
complex_t cx[N];   // complex signal
complex_t X[N];    // DFT
float spectrum[N]; // Spectrum
float Pxx[N];      // PSD

// Control state machine
int state, pstate;
#define DISP_SIG 1
#define DISP_DFT 2
#define DISP_PSD 3

// function to plot line on display
void plotLine(N5110 *display, float points[], int npoints) {

	// find max(point) and min(point)
	float max, min;
	min = max = 0;
	for (int n = 0; n < npoints; n++) {
		max = (points[n] > max) ? points[n] : max;
		min = (points[n] < min) ? points[n] : min;
	}

	// Y-axes
	float zero_point = (0-min)/(max-min); // normalise to [0..1]
	float zero_h = (DISP_HEIGHT-1) - int(zero_point*(DISP_HEIGHT-1)); // px
	display->setPixel(0,zero_h); // set pixel
	display->setPixel(1,zero_h); // set pixel
	for (int h = 0; h < DISP_HEIGHT; h++) {
		display->setPixel(2,h); // set pixel
	}

	// normalise points to screent height
	for (int n = 0; n < npoints; n++) {
		float norm_point = (points[n]-min)/(max-min); // normalise to [0..1]
		float h = (DISP_HEIGHT-1) - int(norm_point*(DISP_HEIGHT-1)); // px
		display->setPixel(n+3,h); // set pixel
	}

	// refresh display
    display->refresh();
}

// Compute DFT
void computeDFT() {

	// convert signal to complex
	for (int n = 0; n < N; n++) cx[n] = complex_num(x[n], 0);

	// init DFT output sequence
	for (int n = 0; n < N; n++) X[n] = complex_num(0, 0); // init to 0

	// compute DFT
	dft(X, cx, N);

	// remove DC component and AC alliases, and spread the rest of the signal
	for (int n = 0; n < N; n++)
		spectrum[n] = 0;
	for (int n = 0; n < floor(N / 2) - 1; n++) {
		spectrum[2 * n] = complex_norm(X[n + 1]);
		spectrum[2 * n + 1] =
				(complex_norm(X[n + 2]) + complex_norm(X[n + 1])) / 2;
	}
}

// Compute PSD
void computePSD() {

	// estimate Power Spectral Density (PSD)
	for (int n = 0; n < N; n++) Pxx[n] = 0; // init to 0
	for (int n = 0; n < floor(N / 2) - 1; n++) {
		Pxx[2 * n] = 20 * log10(pow(complex_norm(X[n + 1]), 2));
		float avg = (complex_norm(X[n + 2]) + complex_norm(X[n + 1])) / 2;
		Pxx[2 * n + 1] = 20 * log10(pow(avg, 2));
	}
}

union sample_union {
	float f;
	unsigned char b[4];
} sample;

// Serial DAQ
void matlab_rx() {

	// get data from Matlab
	for (int n = 0; n < N; n++) {
		x[n] = 0;

		// read number octet by octet
		sample.b[0] = (unsigned char) getc(); // b0
		sample.b[1] = (unsigned char) getc(); // b1
		sample.b[2] = (unsigned char) getc(); // b2
		sample.b[3] = (unsigned char) getc(); // b3

		// save sample
		x[n] = sample.f;
	}

	// DFT
	computeDFT();

	// Periodogram
	computePSD();

	// flag screen to be redraw
	dirty = 1;
}

// Temperature Data-Acquisition thread
void tmp_daq(void const *args) {

	char buffer[30];

	while (1) {
		float avg = 0;

		if (isLoggingOn) {
			// if the file doesn't exist it is created, if it exists, data is appended to the end
			leds = 0xf; // turn on LEDs for feedback
			fp = fopen("/local/log.csv", "a"); // open 'log.csv' for appending
		} else {
			fclose(fp); // close file
			leds = 0x0; // turn off LEDs to signify file access has finished
		}

		// acquire enough samples for the DFT
		for (int n = 0; n < N; n++) {
			float temp = 0;
			// get temperature
			tmp.temp(&temp);
			avg += (x[n] = temp);

			// format time into a string (time and date)
			time_t seconds = time(NULL); // get current time
			strftime(buffer, 30, "%X %D", localtime(&seconds));
			if (isLoggingOn && fp != NULL) {
				// write to local filesystem
				fprintf(fp, "%s, %.2f\n", buffer, temp);
			}

			// 8Hz daq rate (maximum)
			Thread::wait(0.125);

			//wait(60);
		}
		avg /= N;
		// write to serial
		//printf("%s, %.2f\n", buffer, temp);

		// display average temperature
		//char buffer[6] = "";
		//sscanf(buffer,"%f",&avg);
		//display.printString(buffer,65,0);

		// DFT
		computeDFT();

		// Periodogram
		computePSD();

		// flag screen to be redraw
		dirty = 1;
	}
}

// main
int main() {

	set_time(1420753443); // initialise time to 1st January 1970

	// init temperature sensor
	enable = 0;
	tmp.init(1);

	// init LCD display
	dirty = 0;
	display.init();

	// temperature daq thread
	Thread thread(tmp_daq);

	// matlab rx callback
	serial.attach(&matlab_rx);

	// Controller
	pstate = 0,state = DISP_SIG; // init control state machine
	while(1) {

		// Controls
		if (sw) { // SW = 1 - Signal Analysis ...
			if (!a_btn) // Button A - Spectrum display
				state = DISP_DFT;
			if (!b_btn) // Button B - Power Spectral Density display
				state = DISP_PSD;
		} else { // SW = 0 - Temperature display, Logging control ...
			state = DISP_SIG;
			if (!a_btn)  // Button A - Switch logging On (default is Off)
				isLoggingOn = 1;
			if (!b_btn) // Button B - Switch logging Off
				isLoggingOn = 0;
		}

		// State decoder
		char phrase[13];
		if (dirty || pstate != state) {
			display.clear(); // clear display

			switch (state) {
			case DISP_SIG:
				sprintf(phrase,"Temp: %.2f C",x[0]);
				display.printString(phrase,0,0); // print temperature
				break;
			case DISP_DFT:
				plotLine(&display,spectrum,N); // Display Spectrum
				break;
			case DISP_PSD:
				plotLine(&display,Pxx,N); // Display Periodogram
				break;
			default:
				sprintf(phrase,"Temp: %.2f C",x[0]);
				display.printString(phrase,0,0); // print temperature
				break;
			}
			dirty = 0;
			pstate = state;
		}

	}

}
