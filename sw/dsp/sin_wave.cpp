/* sin_wave.c
 *
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Sat 22 Nov 2014
 *
 * This source file contains the implementation of a sinusoidal wave [2] 
 * generator.  
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages—C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 *  [2] Proakis, J. G.; Manolakis D.G., "Digital Signal Processing Principles,
 *      Algorithms, and Applications", 3rd ed., Prentice-Hall, 1996, pp. 2-4.
 *
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#include "sin_wave.h"

// Sinusoidal wave generator
void sin_wave(
  float *x, // is the wave.
  int N,    // is the number of samples.
  float Fs, // is the sampling frequency of the wave.
  float *A, // are the components Amplitudes.
  float *f, // are the components frequencies.
  float *p, // are the components phase shifts (fractions of PI).
  int M     // is the number of components.
  ) {
  
  int n,k;
  
  float T = 1/Fs; // sec/sample
  
  // 0 ≤ n ≤ N-1
  for (n = 0; n < N; n++) {
    x[n] = 0; // init to 0
    // 0 ≤ k ≤ M-1
    for (k = 0; k < M; k++) {
      float t = (n+1)*T; // step in time
      x[n] += A[k]*sin(2*M_PI*f[k]*t + p[k]*M_PI);
    }
  }
  
}
