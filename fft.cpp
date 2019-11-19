#include "fft.h"

vector_t fft (vector_t & vector_in) {

	vector_t vector_out;
	vector_out = vector_in; 

	vector_out = fill0till_exp2 (vector_out); //Redimensiona el vector hasta un longitud 2^n

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

	vector_t vector_out;
	vector_out = vector_in;
	return vector_out;
}

vector_t fill0till_exp2 (vector_t & vector_in) {

	vector_t vector_out = vector_in; //pasar el vector directmente por copia y trabajar sobre eso? o trabajar sobre el vector?
	int largo = vector_out.leng();
	int i, nappends;
	complejo cero;

	for (i = 0; pow(2,i) < largo; i++); //calculando la raiz y redondeandola para abajo no encontrás i?

	nappends = pow(2,i) - largo;

	while (nappends > 0){
		vector_out.append(cero);
		nappends--;
	}

	return vector_out;
}