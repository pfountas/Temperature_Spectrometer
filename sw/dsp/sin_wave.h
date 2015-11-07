/* sin_wave.h
 *
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Sat 22 Nov 2014
 *
 * This source file contains the definition of a sinusoidal wave [2] generator.  
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages�C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 *  [2] Proakis, J. G.; Manolakis D.G., "Digital Signal Processing Principles,
 *      Algorithms, and Applications", 3rd ed., Prentice-Hall, 1996, pp. 2-4.
 *
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#ifndef __C90_SIN_WAVE_H_
#define __C90_SIN_WAVE_H_

#include "mbed.h"


// Sinusoidal wave generator
void sin_wave(
  float *x, // is the wave.
  int N,    // is the number of samples.
  float Fs, // is the sampling frequency of the wave.
  float *A, // are the components Amplitudes.
  float *f, // are the components frequencies.
  float *p, // are the components phase shifts (fractions of PI).
  int M );  // is the number of components.


#endif // __C90_SIN_WAVE_H_
