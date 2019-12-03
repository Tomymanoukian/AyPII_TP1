#include "fft.h"

void fft (vector_t & vector) {

    fill0till_exp2 (vector); //Redimensiona el vector hasta un longitud 2^n
    _fft(vector);
}

void _fft (vector_t & vector) {

    int i, j, largo = vector.leng();
    complejo aux, wn;

    if (vector.leng() >= 2) {

        vector_t vector_par(largo / 2), vector_impar(largo / 2); //crear con tamaño determinado

        for (i = 0, j = 0; i < largo; i += 2, j++) { //Crea el vector con los indices par

            aux = vector[i];
            //vector_par.append(aux);
            vector_par.swap(aux, j);
        }

        for (i = 1, j = 0; i < largo; i += 2, j++) { //Crea el vector con los indices impar
            
            aux = vector[i];
            //vector_impar.append(aux);
            vector_impar.swap(aux,j);
        }

        _fft (vector_par);
        _fft (vector_impar);

        //vector.clean();

        for (i = 0; i < largo/2; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (-sin (2 * M_PI * i / largo));

            aux = vector_par[i] + vector_impar[i] * wn;

            //vector.append(aux);
            vector.swap(aux, i);
        }

        for(; i<largo; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (-sin (2 * M_PI * i / largo));

            aux = vector_par[i - largo/2] + vector_impar[i - largo/2] * wn;

            //vector.append(aux);
            vector.swap(aux, i);
        }
    }
}

void ifft (vector_t & vector) {

    int i, largo;
    complejo aux;

    fill0till_exp2 (vector);
    _ifft (vector);

    largo = vector.leng();

    for (i = 0; i < largo; i++) {
        aux = vector[i] / largo;
        vector.swap(aux, i);
    }
}

void _ifft (vector_t & vector) {

    //vector_t vector_par, vector_impar;
    int i, largo;
    complejo aux, wn;

    largo = vector.leng();

    if (vector.leng() >= 2) {

        vector_t vector_par(largo / 2), vector_impar(largo / 2); //crear con tamaño determinado

        for (i = 0; i < largo; i += 2) {

            aux = vector[i];
            vector_par.append(aux);
        }

        for (i = 1; i < largo; i += 2) {
            
            aux = vector[i];
            vector_impar.append(aux);
        }

        _ifft (vector_par);
        _ifft (vector_impar);

        //vector.clean();

        for (i = 0; i < largo/2; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (sin (2 * M_PI * i / largo));

            aux = (vector_par[i] + vector_impar[i] * wn);
            //vector.append(aux);
            vector.swap(aux, i);
        }

        for(; i<largo; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (sin (2 * M_PI * i / largo));

            aux = (vector_par[i - largo/2] + vector_impar[i - largo/2] * wn);

            //vector.append(aux);
            vector.swap(aux, i);
        }
    }
}

void fill0till_exp2 (vector_t & vector_in) {

    int largo = vector_in.leng();
    double exp2 = log2(largo);
    int sig_exp2, i, int_exp2 = exp2;
    complejo cero;

    if(exp2 - int_exp2){

        sig_exp2 = pow(2, int_exp2 + 1);
        vector_t vector_out(sig_exp2);

        for (i = 0; i < largo; ++i)
        {
            complejo aux = vector_in[i];
            vector_out.swap(aux, i);
        }
        while(i < sig_exp2){
            vector_out.append(cero);
            i++;
        }

        vector_in = vector_out;
    }
}