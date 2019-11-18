#include "fft.h"

vector_t fft (vector_t & vector_in) {

	vector_t vector_out;
	vector_out = vector_in;
	int nappends;

	vector_out = fill0till_exp2(vector_out, nappends);

	_fft(vector_out);

	return vector_out;
}

vector_t _fft (vector_t & vector_in) {

	vector_t vector_out;

	return vector_out;
}

vector_t ifft (vector_t & vector_in) {

	vector_t vector_out;
	vector_out = vector_in;
	return vector_out;
}

vector_t fill0till_exp2 (vector_t & vector_in, int & nappends) {

	vector_t vector_out = vector_in; //pasar el vector directmente por copia y trabajar sobre eso? o trabajar sobre el vector?
	int largo = vector_out.leng();
	int i, j;
	complejo cero;

	for (i = 0; pow(2,i) < largo; i++); //calculando la raiz y redondeandola para abajo no encontrás i?

	nappends = pow(2,i)-largo;

	cout << nappends << endl;

	j = nappends; //porque no usar nappends directamente?

	while (j > 0){ 
		vector_out.append(cero);
		j--;
	}

	return vector_out;
}