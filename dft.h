#ifndef DFT_H
#define DFT_H

#include <iostream>
#include <cmath>
#include "complejo.h"
#include "vector_t.h"

vector_t dft(vector_t & vector_in);
vector_t idft(vector_t & vector_in);

#endif