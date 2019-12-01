#ifndef FFT_H
#define FFT_H

#include <iostream>
#include <cmath>
#include "complejo.h"
#include "vector_t.h"
#include "dft.h"

void fft (vector_t & vector_in);
void _fft (vector_t & vector_in);
void ifft (vector_t & vector_in);
void _ifft (vector_t & vector_in);
void fill0till_exp2 (vector_t & vector_in);

#endif