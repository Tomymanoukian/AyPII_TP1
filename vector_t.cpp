#include <iostream>
#include <sstream> 
#include <string>
    
using namespace std;

#include "vector_t.h"

vector_t::vector_t(){
    
    capacidad = VECTOR_DEFAULT_CAPACIDAD_INICIAL;
    
    p = new complejo[capacidad];
}

vector_t::vector_t(size_t largo){ 
    capacidad = largo;
    tam = largo;
    p = new complejo[capacidad];
}

vector_t::vector_t(const vector_t &copia){

    tam = copia.tam;
    capacidad = copia.capacidad;

    p = new complejo[capacidad];

    for(size_t i = 0; i < capacidad; i++){
        p[i] = copia.p[i];
    }
}

vector_t::~vector_t(){

    delete[] p;
}

size_t vector_t::leng() const{

    return tam;
}

void vector_t::aumentar_cap(size_t cant){

    complejo* aux = new complejo[capacidad + cant];

    for (size_t i = 0; i < capacidad; i++){
        aux[i] = p[i];
    }

    capacidad = capacidad + cant;
    delete[] p;
    p = aux;
}

void vector_t::append(complejo &valor)
{
    if(tam == capacidad){
        aumentar_cap(VECTOR_DEFAULT_STEP);
    }

    p[tam] = valor;
    tam++;
}

bool vector_t::swap(complejo &val, int pos){ 

    if (pos >= 0 && (size_t)pos < tam){

        p[pos/* - 1*/] = val;
        return true;
    }
    else if (pos >= 0 && tam < capacidad &&(size_t)pos < tam + 1){
        p[pos] = val;
        tam++;
        return true;
    }
    else {
        return false;
    }
}

void vector_t::clean()
{
    tam = 0;
    capacidad = VECTOR_DEFAULT_CAPACIDAD_INICIAL;
    delete [] p;
    p = new complejo[capacidad];
}

vector_t vector_t::operator +(const vector_t &a){

    size_t longitud = tam + a.leng();

    if(capacidad < longitud){
        this->aumentar_cap(longitud);
    }

    for (size_t i = 0; i < (size_t)a.leng(); ++i)
    {
        p[this->leng() + i] = a.p[i]; 
    }

    return *this;
}

vector_t& vector_t::operator = (const vector_t &vec){

    tam = vec.tam;
    capacidad = vec.capacidad;

    delete[] p;
    p = new complejo[capacidad];

    for(size_t i = 0; i < capacidad; i++){
        p[i] = vec.p[i];
    }

    return *this;
}

complejo vector_t::operator [](int pos){
    return p[pos];
}

bool vector_t::operator ==(const vector_t &vec){ 

    if(tam != vec.tam)
    {
        return false;
    }

    for(size_t i = 0; i < tam;i++)
    {
        if(!(p[i] == vec.p[i]))
        {
            return false;
        }
    }

    return true;
}

istream & operator >>(istream &is, vector_t &v){ //lee un vector_t de complejos separados por espacios del archivo is

    complejo c;
    string line;

    if(!getline(is, line)){
        return is;
    }

    istringstream stream_line(line);

    while(stream_line >> c){
        v.append(c);
    }

    //En caso de que haya error, cambia estado de is
    if(stream_line.bad()){
        is.clear(ios::badbit);
    }
    
    return is;
}

ostream & operator <<(ostream &os, vector_t &v){

    for (size_t i = 0; i < v.tam; i++)
    {
        os << v[i] << " ";
    }

    return os;
}