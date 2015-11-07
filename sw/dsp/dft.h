/* dft.h
 *
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Thu 20 Nov 2014
 *
 * This source file contains the definition of the Discrete Fourier 
 * Transform [2]. 
 *
 * Dependencies:
 *  "complex_numbers.h", ANSI C90
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages�C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 *  [2] Oppenheim, A. V.; Schafer, R. W.,"Discrete-Time Signal Processing,"
 *      3rd ed., Pearson Prentice Hall, 2010, pp. 652-654,750-751. 
 * 
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#ifndef __C90_DFT_H_
#define __C90_DFT_H_

#include "mbed.h"
#include "complex_numbers.h"


// Discrete Fourier Transform (direct implementation)
void dft(
  complex_t *X, // DFT output of the signal.
  complex_t *x, // input signal.
  int N);       // DFT size (number of samples).


#endif // __C90_DFT_H_
