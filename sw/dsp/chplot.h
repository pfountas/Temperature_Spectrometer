/* chplot.h
 *
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Sat 22 Nov 2014
 *
 * This source file contains the definition of a character display
 * plotter for stdout.  
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages�C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 *
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#ifndef __C90_CHPLOT_H_
#define __C90_CHPLOT_H_

#include "mbed.h"


// Character display plot
void chplot(
  float *x, // point vector 
  int N,    // number of points (X-axis length)
  int M,    // plot height (Y-axis length) 
  char ch,  // character
  Serial *dev); // output device


#endif // __C90_CHPLOT_H_
