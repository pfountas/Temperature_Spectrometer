/* complex_numbers.h
 * 
 * Author: Petros Fountas
 * C90 compliant [1]
 * Created on Thu 20 Nov 2014
 *
 * This header file contains the implementations of the basic complex
 * operations.
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
 *  [1] ISO/IEC, "Programming Languages—C (ISO/IEC 9899:1990)," Geneva,
 *      Switzerland: ISO, 1990.
 * 
 * Last modified on Sat 22 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#include "math.h"

#include "complex_numbers.h"


// Complex Number c = a + bi
complex_t complex_num(float a, float b) {
  
  complex_t c = {a, b};
  
  return c;
  
}


// Real part Re(c)
float complex_real(complex_t c) {
  
  return c.real;
}


// Imaginary part Im(c)
float complex_imag(complex_t c) {
  
  return c.imag;
}


// Complex Norm z = norm(c)
float complex_norm(complex_t c) {
  
  float z = sqrt(pow(c.real,2) + pow(c.imag,2));
    
  return z;
}


// Complex Phase phi = phase(c)
float complex_phase(complex_t c) {
  
  float phi = atan2(c.imag,c.real);
  
  return phi;
}


// Complex Conjugate a-bi = conj(a+bi)
complex_t complex_conj(complex_t c) {
  
  c.imag *= -1.0;
  
  return c;
}


// Complex Exponential z = exp(c)
complex_t complex_exp(complex_t c) {
  
  complex_t z;
  
  z.real = exp(c.real)*cos(c.imag);
  z.imag = exp(c.real)*sin(c.imag);
  
  return z;
}


// Complex Addition c = a + b
complex_t complex_add(complex_t a, complex_t b) {
  
  complex_t c;
  
  c.real = a.real + b.real;
  c.imag = a.imag + b.imag;
  
  return c;
}


// Complex Subtraction c = a - b
complex_t complex_sub(complex_t a, complex_t b) {
  
  complex_t c;
  
  c.real = a.real - b.real;
  c.imag = a.imag - b.imag;
  
  return c;
}


// Complex Multiplication c = a * b
complex_t complex_mul(complex_t a, complex_t b) {
  
  complex_t c;
  
  c.real = a.real*b.real - a.imag*b.imag;
  c.imag = a.real*b.imag + a.imag*b.real;
  
  return c;
}


// Complex Division c = a / b
complex_t complex_div(complex_t a, complex_t b) {
  
  complex_t c;
  
  complex_t nu = complex_mul(a,complex_conj(b));
  complex_t dn = complex_mul(b,complex_conj(b));
  
  c.real = nu.real/dn.real;
  c.imag = nu.imag/dn.real;
  
  return c;
}
