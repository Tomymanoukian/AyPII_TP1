#ifndef FFT_H
#define FFT_H

#include <iostream>
#include <cmath>
#include "complejo.h"
#include "vector_t.h"

vector_t fft(vector_t & vector_in);
vector_t ifft(vector_t & vector_in);

#endif
