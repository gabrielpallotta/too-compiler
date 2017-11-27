#include <iostream>
#include <stdio.h>
#include "header/AnalisadorLexico.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    AnalisadorLexico* analex = new AnalisadorLexico((char*)"teste.pas");

    TipoPedaco tipo;
    while (analex->temMaisPedacos()) {
      tipo = analex->proximoPedaco();
      if (tipo < nPalavras + nOperadores)
        printf("%s\n", palavrasReservadas[tipo]);
      else
      {
        if (tipo == numero)
          printf("Número\n");
        if (tipo == identificador)
          printf("Identificador\n");
      }

    }
    return 0;
}
