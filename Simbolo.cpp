#include "header/Simbolo.h"
#include <vector>

using namespace std;

// Parametro
Parametro::Parametro (TipoVar tipo)
{
	this->tipo = tipo;
}

TipoVar Parametro::getTipo ()
{
	return this->tipo;
}

// Variavel
Variavel::Variavel (TipoVar tipo)
{
	this->tipo = tipo;
}

TipoVar Variavel::getTipo ()
{
	return this->tipo;
}

// Funcao
Funcao::Funcao (TipoVar tipoDeRetorno)
{
	this->tipoDeRetorno = tipoDeRetorno;
	this->parametros = vector<Parametro>();
}

TipoVar Funcao::getTipoDeRetorno ()
{
	return this->tipoDeRetorno;
}

int Funcao::getNumeroParametros ()
{
	return this->parametros.size();
}

//Procedimento
int Procedimento::getNumeroParametros ()
{
	return this->parametros.size();
	this->parametros = vector<Parametro>();
}

void Procedimento::adicionarParametro (Parametro p)
{
	this->parametros.push_back(p);
}
