#ifndef _CMDLINE_H_INCLUDED_
#define _CMDLINE_H_INCLUDED_

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2

#define DFT "dft"
#define IDFT "idft"
#define FFT "fft"
#define IFFT "ifft"

using namespace std;

typedef enum type_method {
    METHOD_DFT,
    METHOD_IDFT,
    METHOD_FFT,
    METHOD_IFFT
} type_method;

struct option_t {
    int has_arg;
    const char *short_name;
    const char *long_name;
    const char *def_value;
    void (*parse)(std::string const &); // Puntero a función de opciones
    int flags;
};

class cmdline {

    option_t *option_table;

    cmdline();
    int do_long_opt(const char *, const char *);
    int do_short_opt(const char *, const char *);
public:
    cmdline(option_t *);
    void parse(int, char * const []);
};

void opt_input(string const &);
void opt_output(string const &);
void opt_method(string const &);
void opt_help(string const &);
///////////////////////
extern option_t options[];

extern type_method method;
extern std::istream *iss;   // Input Stream (clase para manejo de los flujos de entrada)
extern std::ostream *oss;   // Output Stream (clase para manejo de los flujos de salida)
extern std::fstream ifs;        // Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
extern std::fstream ofs;        // Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)
////////////////////////////
#endif
