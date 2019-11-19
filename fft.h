#ifndef FFT_H
#define FFT_H

#include <iostream>
#include <cmath>
#include "complejo.h"
#include "vector_t.h"
#include "dft.h"

vector_t fft(vector_t & vector_in);
vector_t _fft (vector_t & vector_in);
vector_t ifft(vector_t & vector_in);
vector_t fill0till_exp2 (vector_t & vector_in);

#endif