#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <string.h>

#include "complejo.h"
#include "vector_t.h"

using namespace std;

//------------------------------------------------------------
void OperacionSuma(ofstream &, string );
void OperacionIO(ofstream &, string);
void OperacionLargo(ofstream &, string);
void OperacionIgualdad(ofstream &, string);

#define TEST_LARGO_OPCIONES_METODOS 4
char * const Opciones_metodos[] = 
{
    "#+", //0-Prueba el operador suma
    "#STREAM", //1-Prueba el input y el output
    "#LARGO", //2-Prueba el largo del vector
    "#=="  //3-Prueba la igualdad
};

void (*Operaciones[])(ofstream &, string) =
{
    OperacionSuma,
    OperacionIO,
    OperacionLargo,
    OperacionIgualdad
};

//------------------------------------------------------

int main(int argc, char ** argv)
{
    ifstream file_in;
    ofstream file_out;
    string nombre_archivo(argv[1]);
    string line_readed;
    bool operacion_elegida = false;
    
    void (*Operacion_a_probar)(ofstream &, string);

    file_in.open(nombre_archivo);
    file_out.open("out_" + nombre_archivo, ofstream::trunc);

    if(!file_in || !file_out)
    {
        cout << "No se pudo abrir el archivo de prueba\n";
        return 1;
    }

    while(!file_in.eof())
    {
        getline(file_in, line_readed);

        //En caso de que la linea este vacia, saltear
        if(line_readed.empty())
        {
            file_out << endl;
            continue;
        }

        else  //En caso de que sea una de las opciones
        {
            for(int i = 0; i < TEST_LARGO_OPCIONES_METODOS; i++)
            {
                if(strcmp(line_readed.c_str(),Opciones_metodos[i]) == 0)
                {
                    file_out << Opciones_metodos[i] << endl;
                    Operacion_a_probar = Operaciones[i];
                    operacion_elegida = true;
                }
            }
        }

        if(operacion_elegida) //Salteo esta iteracion si hubo un metodo elegido
        {
            operacion_elegida = false;
            continue;
        }

        Operacion_a_probar(file_out, line_readed); //Pruebo la operacion
    }

    file_in.close();
    file_out.close();
}

void OperacionSuma(ofstream & out, string line){return;}

void OperacionIO(ofstream & out, string line){

    vector_t vector_prueba;
    string print_line = line.substr(0, line.find_last_of("="));
    stringstream string_buffer(print_line);

    out << print_line << " = ";
    string_buffer >>  vector_prueba;

    if(string_buffer.bad())
    {
        out << "ERROR" << endl;
        return;
    }

    out << vector_prueba << endl;
    return;
}

void OperacionLargo(ofstream & out, string line){

    vector_t vector_prueba;
    string print_line = line.substr(0, line.find_last_of("="));
    stringstream string_buffer(print_line);

    out << print_line << " = ";
    string_buffer >>  vector_prueba;

    if(string_buffer.bad())
    {
        out << "ERROR" << endl;
        return;
    }

    out << vector_prueba.leng() << endl;
    return;
}

void OperacionIgualdad(ofstream & out, string line){
    
    vector_t vector_izquierdo, vector_derecho;
    string print_line = line.substr(0, line.find_last_of("="));
    string line_after_operator = print_line.substr(print_line.find_first_of("=") + 1);

    out << print_line << " = ";
    
    stringstream buffer_izquierdo(print_line.substr(0,print_line.find_first_of("=")));
    stringstream buffer_derecho(line_after_operator.substr(1,line_after_operator.size()-1)); //Borro basura
    
    buffer_izquierdo >> vector_izquierdo;
    buffer_derecho >> vector_derecho;

    if(vector_izquierdo == vector_derecho)
    {
        out << "TRUE" << endl;
        return;
    }

    out << "FALSE" << endl;
    return;
}