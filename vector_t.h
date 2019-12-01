#ifndef VECTOR_T__H
#define VECTOR_T__H

#define VECTOR_DEFAULT_CAPACIDAD_INICIAL 10
#define VECTOR_DEFAULT_STEP 5

#include <iostream>
#include "complejo.h"

using namespace std;

class vector_t
{
private:
    complejo* p;
    size_t tam = 0;
    size_t capacidad = 0;

    void aumentar_cap(size_t cant); 

public:
    vector_t();
    vector_t(size_t largo);
    vector_t(const vector_t &copia);
    ~vector_t();
    

    size_t leng() const; //Devuelve el tamaño del vector
    void append(complejo &valor); //Agrega el complejo al final del vector
    bool swap(complejo &val, int pos); //Cambia el valor del complejo en la posición seleccionada
    void clean(); //Limpia el vector y lo devuelve a la capacidad default;

    vector_t operator+(const vector_t &a);
    complejo operator[](int pos);
    vector_t& operator = (const vector_t &vec);
    bool operator==(const vector_t &vec);

    friend istream & operator>>(istream &is, vector_t &v);
    friend ostream & operator<<(ostream &os, vector_t &v);

};

#endif
