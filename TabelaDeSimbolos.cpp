#include "header/TabelaDeSimbolos.h"
#include <vector>
#include <string.h>
#include <string>

using namespace std;

TabelaDeSimbolos::TabelaDeSimbolos()
{
    listaDeSimbolos = vector<vector<Simbolo*> >();
}

void TabelaDeSimbolos::guarde(Simbolo* s)
{
	listaDeSimbolos.back().push_back(s);
}

void TabelaDeSimbolos::adicioneNivel()
{
	listaDeSimbolos.push_back(vector<Simbolo*>());
}

void TabelaDeSimbolos::elimineNivel()
{
	listaDeSimbolos.pop_back();
}

Simbolo* TabelaDeSimbolos::getSimbolo(char* s, int nivel)
{
    int i = 0;
	while (i < listaDeSimbolos.size())
        if (strcmp(listaDeSimbolos[nivel][i]->nome, s) == 0)
            return listaDeSimbolos[nivel][i];

    return 0;
}
