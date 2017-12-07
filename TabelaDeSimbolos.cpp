#include "header/TabelaDeSimbolos.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <stack>

using namespace std;

TabelaDeSimbolos::TabelaDeSimbolos()
{
    nivelAtual = 0;
    listaDeSimbolos = vector<vector<Simbolo*> >();
    nomes = stack<char*>();
}

void TabelaDeSimbolos::guarde(Simbolo* s)
{
    cout << s->nome << " - " << nivelAtual  << "\n";
	listaDeSimbolos.back().push_back(s);
}

void TabelaDeSimbolos::adicioneNivel(char* nome)
{
    nomes.push(nome);
    nivelAtual++;
	listaDeSimbolos.push_back(vector<Simbolo*>());
}

void TabelaDeSimbolos::elimineNivel()
{
    nomes.pop();
    nivelAtual--;
	listaDeSimbolos.pop_back();
}

Simbolo* TabelaDeSimbolos::getSimbolo(char* s)
{
    for (int i = listaDeSimbolos.size() - 1; i >= 0; i--)
        for (int j = 0; j < listaDeSimbolos[i].size(); j++)
            if (strcmp(listaDeSimbolos[i][j]->nome, s) == 0)
                return listaDeSimbolos[i][j];

    return 0;
}


char* TabelaDeSimbolos::getNomeNivel()
{
    return nomes.top();
}

