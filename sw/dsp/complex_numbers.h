/* complex_numbers.h
 * 
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Thu 20 Nov 2014
 *
 * This header file contains the definition of the complex number and the
 * declarations of the basic complex operations.
 *
 * Complex type is defined as structure
 *
 *      { real: float, imag: float }
 *
 * and is associated with the user defined type:
 *
 *                complex_t
 *
 * The following operations are supported for complex types:
 *
 *  Supported Operations    | Usage                     | Output    | Input
 *  ---------------------------------------------------------------------------
 *  Complex Number          | c = complex_num(re,im)    | complex_t | float
 *  Real part               | re = complex_real(c)      | float     | complex_t
 *  Imaginary part          | im = complex_imag(c)      | float     | complex_t
 *  Complex Norm            | z = complex_norm(c)       | float     | complex_t
 *  Complex Phase (radians) | phi = complex_phase(c)    | float     | complex_t
 *  Complex Conjugate       | a-bi = complex_conj(a+bi) | complex_t | complex_t
 *  Complex Exponential     | z = complex_exp(c)        | complex_t | complex_t
 *  Complex Addition        | c = complex_add(a,b)      | complex_t | complex_t
 *  Complex Subtraction     | c = complex_sub(a,b)      | complex_t | complex_t
 *  Complex Multiplication  | c = complex_mul(a,b)      | complex_t | complex_t
 *  Complex Division        | c = complex_div(a,b)      | complex_t | complex_t
 *
 *  Utilities               | Usage                     | Output    | Input
 *  ---------------------------------------------------------------------------
 *  Print complex number    | complex_print(c)          | N/A       | complex_t
 *
 * Dependencies:
 *  "math.h", ANSI C90
 *
 * References:
 *  [1] ISO/IEC, "Programming Languages�C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 * 
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#ifndef __C90_COMPLEX_NUMBERS_H_
#define __C90_COMPLEX_NUMBERS_H_

#include "mbed.h"

// Print complex number to stdout
#define complex_print(c) \
  printf("%.2f %+.2fi\n", complex_real(c), complex_imag(c))

/* Complex Type
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Number." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexNumber.html 
 */
typedef struct {
  float real;
  float imag;
} complex_t;


/* Complex Number c = a + bi
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Number." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexNumber.html 
 */
complex_t complex_num(float a, float b);


/* Real part Re(c)
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Number." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexNumber.html 
 */
float complex_real(complex_t c);


/* Imaginary part Im(c)
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Number." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexNumber.html 
 */
float complex_imag(complex_t c);


/* Complex Norm z = norm(c)
 * 
 * References:
 *  [1]  Weisstein, Eric W. "Complex Modulus." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexModulus.html  
 */
float complex_norm(complex_t c);


/* Complex Phase phi = phase(c)
 *
 * References:
 *  [1]  Weisstein, Eric W. "Phasor." From MathWorld--A Wolfram Web Resource.
 *       http://mathworld.wolfram.com/Phasor.html  
 */
float complex_phase(complex_t c);

/* Complex Conjugate a-bi = conj(a+bi)
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Conjugate." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexConjugate.html 
 */
complex_t complex_conj(complex_t c);


/* Complex Exponential z = exp(c)
 * 
 * References:
 *  [1]  Weisstein, Eric W. "Exponential Function." From MathWorld--A Wolfram
 *       Web Resource. http://mathworld.wolfram.com/ExponentialFunction.html
 *  [2]  Weisstein, Eric W. "Complex Exponentiation." From MathWorld--A Wolfram
 *       Web Resource. http://mathworld.wolfram.com/ComplexExponentiation.html 
 */
complex_t complex_exp(complex_t c);


/* Complex Addition c = a + b
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Addition." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexAddition.html 
 */
complex_t complex_add(complex_t a, complex_t b);


/* Complex Subtraction c = a - b
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Subtraction." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexSubtraction.html 
 */
complex_t complex_sub(complex_t a, complex_t b);


/* Complex Multiplication c = a * b
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Multiplication." From MathWorld--A Wolfram
 *       Web Resource. http://mathworld.wolfram.com/ComplexMultiplication.html 
 */
complex_t complex_mul(complex_t a, complex_t b);


/* Complex Division c = a / b
 *
 * References:
 *  [1]  Weisstein, Eric W. "Complex Division." From MathWorld--A Wolfram Web
 *       Resource. http://mathworld.wolfram.com/ComplexDivision.html 
 */
complex_t complex_div(complex_t a, complex_t b);

#endif // __C90_COMPLEX_NUMBERS_H_
