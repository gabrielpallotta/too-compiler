#include <iostream>
#include "header/AnalisadorSintatico.h"
#include <stdexcept>
using namespace std;

int main()
{
    AnalisadorSintatico* anasint = new AnalisadorSintatico("programa.pas");
    try
    {
        anasint->compilaInicioDePrograma();
    }
    catch (runtime_error& e)
    {
        cout << e.what();
    }
}
