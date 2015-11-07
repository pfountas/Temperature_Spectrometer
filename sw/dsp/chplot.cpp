/* chplot.c
 *
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Sat 22 Nov 2014
 *
 * This source file contains the implementation of a character display
 * plotter for stdout.  
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages—C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 *
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#include "chplot.h"

#define putchar(c) dev->putc(c)

void chplot(
  float *x, // point vector
  int N,    // number of points (X-axis length)
  int M,    // plot height (Y-axis length)
  char ch,  // character
  Serial *dev) { // output device

  int n,m;
  
  // find max(x) min(x)
  float xmax, xmin;
  xmax = xmin = x[0]; 
  for (n = 1; n < N; n++) {
	xmax = (x[n] > xmax)? x[n] : xmax;
	xmin = (x[n] < xmin)? x[n] : xmin;
  }
  
  // 0 ≤ m ≤ M-1
  for (m = 0; m < M; m++) {

	float xlevel = M-m-1.0; // level on X-axis

	// 0 ≤ n ≤ N-1
	for (n = 0; n < N; n++) {
	  // normalise x[n] to 90% of 0..M
	  float xnorm = floor((x[n]/xmax)*M*0.9); // only positive Y-Axis
	  if (xmin < 0) { // there are negative components
		xnorm = floor((x[n]/xmax)*floor(M/2)*0.9);
		xnorm = (xmin < 0 && x[n] < 0)?
		  floor(M/2)-(-1)*xnorm : // negative Y-Axis
		  xnorm+floor(M/2);       // positive Y-Axis
	  }

	  if (xnorm == xlevel)
		putchar(ch); // mark point
	  else
		putchar(' '); // don't mark point
	}

	putchar('\n'); // change line
  }
  
}
