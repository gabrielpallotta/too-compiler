#include "header/TabelaDeSimbolos.h"
#include <vector>

using namespace std;

TabelaDeSimbolos::TabelaDeSimbolos()
{
    listaDeSimbolos = vector<vector<Simbolo> >();
}

void TabelaDeSimbolos::guarde(Simbolo s)
{
	listaDeSimbolos.back().push_back(s);
}

void TabelaDeSimbolos::adicioneNivel()
{
	listaDeSimbolos.push_back(vector<Simbolo>());
}

void TabelaDeSimbolos::elimineNivel()
{
	listaDeSimbolos.pop_back();
}

bool TabelaDeSimbolos::getSimbolo(string s, int nivel)
{
	return listaDeSimbolos[nivel].exists(s);
}

Simbolo TabelaDeSimbolos::getSimbolo(string s)
{
	//verificação linear da lista de símbolos para devolver o símbolo.
}