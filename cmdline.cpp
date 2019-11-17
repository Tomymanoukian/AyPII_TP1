#include "cmdline.h"
#include "commands_MSG.h"

using namespace std;

cmdline::cmdline(){
}

cmdline::cmdline(option_t *table) : option_table(table){
}

void cmdline::parse(int argc, char * const argv[]){

#define END_OF_OPTIONS(p) ((p)->short_name == 0 && (p)->long_name == 0 && (p)->parse == 0)

    for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op)
        op->flags &= ~OPT_SEEN;

    for (int i = 1; i < argc; ++i){
        
        if (argv[i][0] != '-') 
        {
            cerr << ARGUMENTO_INVALIDO
                 << argv[i]
                 << endl;
            exit(1);
        }

        if (argv[i][1] == '-'
            && argv[i][2] == 0)
            break;

        if (argv[i][1] == '-')
            i += do_long_opt(&argv[i][2], argv[i + 1]);
        else
            i += do_short_opt(&argv[i][1], argv[i + 1]);
    }

    for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op) {
#define OPTION_NAME(op) (op->short_name ? op->short_name : op->long_name)
        if (op->flags & OPT_SEEN)
            continue;
        if (op->flags & OPT_MANDATORY) {
            cerr << "Opcion obligatoria "
                 << "-"
                 << OPTION_NAME(op)
                 << " no ingresada."
                 << "\n";
            exit(1);
        }
        if (op->def_value == 0)
            continue;
        op->parse(string(op->def_value));
    }
}

int cmdline::do_long_opt(const char *opt, const char *arg){

    for (option_t *op = option_table; op->long_name != 0; ++op) {
        if (string(opt) == string(op->long_name)) {

            op->flags |= OPT_SEEN;

            if (op->has_arg) {

                if (arg == 0) {
                    cerr << FALTA_ARGUMENTO
                         << "--"
                         << opt
                         << "\n";
                    exit(1);
                }
                op->parse(string(arg));
                return 1;
            } else {

                op->parse(string(""));
                return 0;
            }
        }
    }

    cerr << OPCION_DESCONOCIDA << "--" << opt << "." << endl;
    exit(1);

    return -1;
}

int cmdline::do_short_opt(const char *opt, const char *arg){

    option_t *op;

    for (op = option_table; op->short_name != 0; ++op) {
        if (string(opt) == string(op->short_name)) {

            op->flags |= OPT_SEEN;

            if (op->has_arg) {

                if (arg == 0) {
                    cerr << FALTA_ARGUMENTO
                         << "-"
                         << opt
                         << "\n";
                    exit(1);
                }
                op->parse(string(arg));
                return 1;
            } else {

                op->parse(string(""));
                return 0;
            }
        }
    }

    cerr << OPCION_DESCONOCIDA
         << "-"
         << opt
         << "."
         << endl;
    exit(1);

    return -1;
}

void opt_input(string const &arg){

    // Si el nombre del archivos es "-", usaremos la entrada
    // estándar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    //
    if (arg == "-") {
        iss = &cin;     // Establezco la entrada estandar cin como flujo de entrada
    }
    else {
        ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
                                        // sequence of characters (i.e., a C-string) representing
                                        // the current value of the string object.
        iss = &ifs;
    }

    // Verificamos que el stream este OK.
    //
    if (!iss->good()) {
        cerr << FALLO_ABRIR
             << arg
             << "."
             << endl;
        exit(1);
    }
}

void opt_output(string const &arg){

    // Si el nombre del archivos es "-", usaremos la salida
    // estándar. De lo contrario, abrimos un archivo en modo
    // de escritura.
    //
    if (arg == "-") {
        oss = &cout;    // Establezco la salida estandar cout como flujo de salida
    } else {
        ofs.open(arg.c_str(), ios::out);
                //printf("Prueba\n");

        oss = &ofs;
    }

    // Verificamos que el stream este OK.
    //
    if (!oss->good()) {
        cerr << "cannot open "
             << arg
             << "."
             << endl;
        exit(1);        // EXIT: Terminación del programa en su totalidad
    }
}

void opt_method(string const &arg){

    if(arg.compare(IDFT)==0) {
        method=METHOD_IDFT;
    } else if (arg.compare(DFT)!=0 && arg.compare("-")!=0) {
        cout<<METODO_INVALIDO<<endl;
        exit(1);
    }
}

void opt_help(string const &arg){
    
    cout << MSJ_AYUDA << endl;
    exit(0);
}
