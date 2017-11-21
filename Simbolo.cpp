#include "header/Simbolo.h"
#include <vector>

using namespace std;

// Parametro
Parametro::Parametro (Tipo tipo)
{
	this->tipo = tipo;
}

Tipo Parametro::getTipo ()
{
	return this->tipo;
}

// Variavel
Variavel::Variavel (Tipo tipo)
{
	this->tipo = tipo;
}

Tipo Variavel::getTipo ()
{
	return this->tipo;
}

// Funcao
Funcao::Funcao (Tipo tipoDeRetorno)
{
	this->tipoDeRetorno = tipoDeRetorno;
	this->parametros = vector<Parametro>();
}

Tipo Funcao::getTipoDeRetorno ()
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
