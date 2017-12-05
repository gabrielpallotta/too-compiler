#include "header/Simbolo.h"
#include <vector>

using namespace std;

Simbolo::Simbolo()
{}

Simbolo::Simbolo(char* nome, int nivel, TipoSimbolo tiposimb)
{
    this->nome = nome;
    this->nivel = nivel;
    this->tiposimb = tiposimb;
}

// Parametro
Parametro::Parametro (char* nome, int nivel, TipoVar tipo, TipoSimbolo tiposimb) : Simbolo(nome, nivel, tiposimb)
{
	this->tipo = tipo;
}

TipoVar Parametro::getTipo ()
{
	return this->tipo;
}

// Variavel
Variavel::Variavel (char* nome, int nivel, TipoVar tipo, TipoSimbolo tiposimb) : Simbolo(nome, nivel, tiposimb)
{
	this->tipo = tipo;
}

TipoVar Variavel::getTipo ()
{
	return this->tipo;
}

// Funcao
Funcao::Funcao (char* nome, int nivel, TipoVar tipoDeRetorno, TipoSimbolo tiposimb) : Simbolo(nome, nivel, tiposimb)
{
	this->tipoDeRetorno = tipoDeRetorno;
	this->parametros = vector<Parametro*>();
}

TipoVar Funcao::getTipoDeRetorno ()
{
	return this->tipoDeRetorno;
}

int Funcao::getNumeroParametros ()
{
	return this->parametros.size();
}

void Funcao::adicionarParametro (Parametro* p)
{
	this->parametros.push_back(p);
}

Parametro* Funcao::getParametro (string s)
{
	// retorna null se não achar parametro
	// retorna parametro se achar
}

//Procedimento
Procedimento::Procedimento(char* nome, int nivel, TipoSimbolo tiposimb) : Simbolo(nome, nivel, tiposimb)
{
	this->parametros = vector<Parametro*>();
}

int Procedimento::getNumeroParametros ()
{
	return this->parametros.size();
}

void Procedimento::adicionarParametro (Parametro* p)
{
	this->parametros.push_back(p);
}

Parametro* Procedimento::getParametro (string s)
{
	// retorna null se não achar parametro
	// retorna parametro se achar
}
