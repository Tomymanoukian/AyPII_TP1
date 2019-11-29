#include <iostream>
#include <fstream>
    using namespace std;
#include "complejo.h"

#define CANT_CMPLX 100000

int main(int argc, char const *argv[])
{
    string name_file = "complejos";
    ofstream file(name_file);

    for (int i = 0; i < CANT_CMPLX; ++i)
    {
        file << " 1 ";
    }

    file.close();
    return 1;
}