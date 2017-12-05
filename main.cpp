#include <iostream>
#include "header/AnalisadorSintatico.h"
#include <stdexcept>
using namespace std;

int main()
{
    AnalisadorSintatico* anasint = new AnalisadorSintatico((char*)"test/Certo.pas");
    try
    {
        anasint->compilaInicioDePrograma();
        cout << "Programa compilado com sucesso!!!!!";
    }
    catch (runtime_error& e)
    {
        cout << e.what();
    }
}
