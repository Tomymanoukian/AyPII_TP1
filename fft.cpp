#include "fft.h"

vector_t fft (vector_t & vector_in) {

    vector_t vector_out = vector_in; 

    vector_out = fill0till_exp2 (vector_out); //Redimensiona el vector hasta un longitud 2^n
    //esta función no necesita retornar nada si se le pasa el vector por referencia y trabaja sobre eso
    //además nos ahorramos el tiempo del copiado y de la asignación

    return _fft (vector_out);
}

vector_t _fft (vector_t & vector_in) {

    vector_t vector_out, vector_in_par, vector_in_impar, vector_out_par, vector_out_impar;
    int i, largo;
    complejo aux, wn;

    largo = vector_in.leng();

    if (vector_in.leng() >= 2) {

        for (i = 0; i < largo; i += 2) { //Crea el vector con los indices par

            aux = vector_in[i];
            vector_in_par.append(aux);
        }

        for (i = 1; i < largo; i += 2) { //Crea el vector con los indices impar
            
            aux = vector_in[i];
            vector_in_impar.append(aux);
        }

        vector_out_par = _fft (vector_in_par);
        vector_out_impar = _fft (vector_in_impar);

        for (i = 0; i < largo/2; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (-sin (2 * M_PI * i / largo));

            aux = vector_out_par[i] + vector_out_impar[i] * wn;

            vector_out.append(aux);
        }

        for(; i<largo; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (-sin (2 * M_PI * i / largo));

            aux = vector_out_par[i - largo/2] + vector_out_impar[i - largo/2] * wn;

            vector_out.append(aux);
        }

    } else {

        vector_out = vector_in;
    }

    return vector_out;
}

vector_t ifft (vector_t & vector_in) {

    vector_t vector_out = vector_in, vector_aux;
    int i, largo;
    complejo aux;

    vector_out = fill0till_exp2 (vector_out);
    vector_out = _ifft (vector_out);

    largo = vector_out.leng();

    for(i=0; i < largo; i++) {        //Este for de acá es un asco, estuve como 2 horas intentando mejorarlo/hacerlo mas lindo. Si les sale, excelente
        aux = vector_out[i] / largo;  //Lo que busca es recorrer todo el vector out y dividir cada posicion por largo
        vector_aux.append(aux);       //Idealmente lo hubiera hecho con swap sobre vector_out directamente, pero no paraba de tirarme errores de memoria
    }                                 //Así que bueno (:

    return vector_aux;
}

vector_t _ifft (vector_t & vector_in) {

    vector_t vector_out, vector_in_par, vector_in_impar, vector_out_par, vector_out_impar;
    int i, largo;
    complejo aux, wn;

    largo = vector_in.leng();

    if (vector_in.leng() >= 2) {

        for (i = 0; i < largo; i += 2) {

            aux = vector_in[i];
            vector_in_par.append(aux);
        }

        for (i = 1; i < largo; i += 2) {
            
            aux = vector_in[i];
            vector_in_impar.append(aux);
        }

        vector_out_par = _ifft (vector_in_par);
        vector_out_impar = _ifft (vector_in_impar);

        for (i = 0; i < largo/2; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (sin (2 * M_PI * i / largo));

            aux = (vector_out_par[i] + vector_out_impar[i] * wn);

            vector_out.append(aux);
        }

        for(; i<largo; i++) {

            wn.set_re (cos (2 * M_PI * i / largo));
            wn.set_im (sin (2 * M_PI * i / largo));

            aux = (vector_out_par[i - largo/2] + vector_out_impar[i - largo/2] * wn);

            vector_out.append(aux);
        }

    } else {

        vector_out = vector_in;
    }

    return vector_out;
}

vector_t fill0till_exp2 (vector_t vector_in) {

    int largo = vector_in.leng();
    int i, nappends;
    complejo cero;

    for (i = 0; pow(2,i) < largo; i++);
    nappends = pow(2,i) - largo;

    while (nappends > 0){
        vector_in.append(cero);
        nappends--;
    }

    return vector_in;
}