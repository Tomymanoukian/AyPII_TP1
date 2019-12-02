#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

#include "cmdline.h"
#include "complejo.h"
#include "vector_t.h"
#include "dft.h"
#include "fft.h"

#define MSJ_ERR_VEC_CORRPUTO_1 "El vector de la línea "
#define MSJ_ERR_VEC_CORRPUTO_2 " se encuentra corrupto, es imposible transformar"

using namespace std;

option_t options[] = {
    {1, "i", "input", "-", opt_input, OPT_DEFAULT},
    {1, "o", "output", "-", opt_output, OPT_DEFAULT},
    {1, "m", "method", "-", opt_method, OPT_DEFAULT},
    {0, "h", "help", NULL, opt_help, OPT_DEFAULT},
    {0, },
};

std::istream *iss=0;    // Input Stream (clase para manejo de los flujos de entrada)
std::ostream *oss=0;    // Output Stream (clase para manejo de los flujos de salida)
std::fstream ifs;       // Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
std::fstream ofs;       // Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)
type_method method = METHOD_FFT;

int main (int argc, char * const argv[])
{
    cmdline cmdl(options);
    cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

    vector_t vec_in; 
    vector_t vec_out;
    size_t num_linea = 1;

    if (method != METHOD_DFT && method != METHOD_IFFT && method != METHOD_IDFT)
        method = METHOD_FFT;

    while(!iss->eof()){

        if(!(*iss >> vec_in)){

            if(iss -> eof()){
                break;
            }

            if(oss != &cout){
                *oss << endl;
            }

            cout << MSJ_ERR_VEC_CORRPUTO_1 << num_linea << MSJ_ERR_VEC_CORRPUTO_2 << endl;

            iss->clear(ios::goodbit); 
            vec_in.clean();
            vec_out.clean();
            num_linea++;
            
            continue;
        }

        if (method == METHOD_FFT) {

            fft(vec_in);

            *oss << vec_in << "\n";

            vec_in.clean();
            num_linea++;

        } else if (method == METHOD_IFFT) {
            
            ifft(vec_in);

            *oss << vec_in << "\n";

            vec_in.clean();
            num_linea++;
        }

        else if (method == METHOD_DFT) {

            vec_out = dft(vec_in);

            *oss << vec_out << "\n";

            vec_in.clean();
            vec_out.clean();
            num_linea++;

        } else if (method == METHOD_IDFT) {

            vec_out = idft(vec_in);

            *oss << vec_out << "\n";

            vec_in.clean();
            vec_out.clean();
            num_linea++;
        }
    }
    
    cout<<flush;

    if(ifs.is_open())
        ifs.close();

    if(ofs.is_open())
        ofs.close();

    return 0;
}
