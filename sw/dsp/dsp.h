/* dsp.h
 * 
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Sat 22 Nov 2014
 *
 * This header file includes header files, which contain the definitions of
 * basic DSP operations and utilities.
 *
 * The following operations are included:
 * 
 * | Operation         | Usage      
 * ---------------------------------------------------------------------------- 
 * | DFT               | dft(X,x,N),
 * | (dft.h)           |  out X:complex_t[N], is the DFT of the signal.
 * |                   |  in  x:complex_t[N], is a signal.
 * |                   |  
 *
 * The following utilities are included:
 * 
 * | Utility           | Usage      
 * ----------------------------------------------------------------------------
 * | Character Plot    | chplot(x,N,M,ch),
 * | (chplot.h)        |  in  x:float[N], is the point vactor.
 * |                   |  in  N:int, is the number of points (X-axis length).
 * |                   |  in  M:int, is the plot height (Y-axis length).
 * |                   |  in  ch:char, is the character, e.g. '*'.
 * |                   |
 * | Sine Wave         | sin_wave(x,Fs,A,f,p,N),
 * | (sin_wave.h)      |  out x:float[N], is the wave.
 * |                   |  in  N:int, is the number of samples.
 * |                   |  in  Fs:float, is the sampling frequency of the wave.
 * |                   |  in  A:float[N], are the components Amplitudes.
 * |                   |  in  f:float[N], are the components frequencies.
 * |                   |  in  p:float[N], are the components phase shifts 
 * |                   |                  expressed as fractions of PI.
 * |                   |  in  M:int, is the number of components.
 * |                   |
 * 
 * Dependencies:
 *  "complex_numbers.h", ANSI C90
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages—C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 * 
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#ifndef __C90_DSP_H_
#define __C90_DSP_H_

#include "complex_numbers.h"
#include "dft.h"
#include "sin_wave.h"
#include "chplot.h"


#endif // __C90_DSP_H_
