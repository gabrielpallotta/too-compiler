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

void TabelaDeSimbolos::elimine()
{
	listaDeSimbolos.pop_back();
}
