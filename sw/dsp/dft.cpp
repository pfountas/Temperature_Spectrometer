/* dft.c
 *
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Thu 20 Nov 2014
 *
 * This source file contains the implementation of the Discrete Fourier 
 * Transform [2]. 
 *
 * Dependencies:
 *  "complex_numbers.h", ANSI C90
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages—C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 *  [2] Oppenheim, A. V.; Schafer, R. W.,"Discrete-Time Signal Processing,"
 *      3rd ed., Pearson Prentice Hall, 2010, pp. 652-654,750-751. 
 * 
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#include "dft.h"

// Discrete Fourier Transform (direct implementation)
void dft(
  complex_t *y, // DFT output of the signal.
  complex_t *x, // input signal.
  int N) {      // DFT size (number of samples).
  
  int k,n;
  
  // 0 ≤ k ≤ N-1
  for (k = 0; k < N; k++)
    // 0 ≤ n ≤ N-1
    for (n = 0; n < N; n++) {
      // y[k] = ∑ x[n]･W(N)^(k*n), W(N) = exp(-j･2𝜋/N) 
      complex_t kn = complex_num(0, -2*M_PI*k*n/N);
      y[k] = complex_add(y[k], complex_mul(x[n], complex_exp(kn)));
    }
  
}
