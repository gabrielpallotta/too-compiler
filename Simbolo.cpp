#include "header/Simbolo.h"
#include <vector>

using namespace std;

Simbolo::Simbolo()
{}

Simbolo::Simbolo(char* nome, int nivel)
{
    this->nome = nome;
    this->nivel = nivel;
}

// Parametro
Parametro::Parametro (char* nome, int nivel, TipoVar tipo)
{
    Simbolo(nome, nivel);
	this->tipo = tipo;
}

TipoVar Parametro::getTipo ()
{
	return this->tipo;
}

// Variavel
Variavel::Variavel (char* nome, int nivel, TipoVar tipo)
{
    Simbolo(nome, nivel);
	this->tipo = tipo;
}

TipoVar Variavel::getTipo ()
{
	return this->tipo;
}

// Funcao
Funcao::Funcao (char* nome, int nivel, TipoVar tipoDeRetorno)
{
    Simbolo(nome, nivel);
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

//Procedimento
Procedimento::Procedimento(char* nome, int nivel)
{
    Simbolo(nome, nivel);
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

Parametro Procedimento::getParametro (string s)
{
	// retorna null se não achar parametro
	// retorna parametro se achar
}
