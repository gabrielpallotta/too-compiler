#include "header/TabelaDeSimbolos.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <string>

using namespace std;

TabelaDeSimbolos::TabelaDeSimbolos()
{
    nivelAtual = 0;
    listaDeSimbolos = vector<vector<Simbolo*> >();
}

void TabelaDeSimbolos::guarde(Simbolo* s)
{
    cout << s->nome;
	listaDeSimbolos.back().push_back(s);
}

void TabelaDeSimbolos::adicioneNivel()
{
    nivelAtual++;
	listaDeSimbolos.push_back(vector<Simbolo*>());
}

void TabelaDeSimbolos::elimineNivel()
{
    nivelAtual--;
	listaDeSimbolos.pop_back();
}

Simbolo* TabelaDeSimbolos::getSimbolo(char* s)
{
    for (int i = listaDeSimbolos.size(); i >= 0; i--)
        for (int j = 0; j < listaDeSimbolos[i].size(); j++)
            if (strcmp(listaDeSimbolos[i][j]->nome, s) == 0)
                return listaDeSimbolos[i][j];

    return 0;
}
