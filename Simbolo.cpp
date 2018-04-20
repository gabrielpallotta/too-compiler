#include "header/Simbolo.h"
#include <vector>

using namespace std;

Simbolo::Simbolo()
{}

Simbolo::Simbolo(char* nome, int nivel, TipoVar tipo, TipoSimbolo tiposimb)
{
    this->nome = nome;
    this->nivel = nivel;
    this->tipo = tipo;
    this->tiposimb = tiposimb;
}

// Variavel
Variavel::Variavel (char* nome, int nivel, TipoVar tipo, TipoSimbolo tiposimb) : Simbolo(nome, nivel, tipo, tiposimb)
{}

// Metodo
Metodo::Metodo (char* nome, int nivel, TipoVar tipoDeRetorno, TipoSimbolo tiposimb) : Simbolo(nome, nivel, tipoDeRetorno, tiposimb)
{
	this->parametros = vector<Variavel*>();
}

int Metodo::getNumeroParametros ()
{
	return this->parametros.size();
}

void Metodo::adicionarParametro (Variavel* p)
{
	this->parametros.push_back(p);
}

Variavel* Metodo::getParametro (int i)
{
    if (i >= this->parametros.size() || i < 0)
        return NULL;
    else
        return this->parametros[i];
}
