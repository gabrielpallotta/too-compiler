#ifndef Simbolo_H
#define Simbolo_H

#include <vector>
#include <string>

using namespace std;

typedef enum
{
    simb_funcao,
    simb_variavel,
    simb_parametro,
    simb_procedimento
} TipoSimbolo;

typedef enum
{
    var_inteiro,
    var_booleano
} TipoVar;

class Simbolo
{
	public:
		char* nome;
		unsigned char nivel;
		TipoSimbolo tiposimb;
		Simbolo(char*, int, TipoSimbolo);
		Simbolo();
};

class Parametro: public Simbolo
{
	private:
		TipoVar tipo;
	public:
		Parametro(char[256], int, TipoVar, TipoSimbolo);
		TipoVar getTipo();
};


class Variavel: public Simbolo
{
	private:
		TipoVar tipo;
	public:
		Variavel(char[256], int, TipoVar, TipoSimbolo);
		TipoVar getTipo();
};

class Funcao: public Simbolo
{
	private:
		TipoVar tipoDeRetorno;
		vector<Parametro*> parametros;
	public:
		Funcao(char[256], int, TipoVar, TipoSimbolo);
		int getNumeroParametros();
		void adicionarParametro(Parametro*);
		TipoVar getTipoDeRetorno();
};

class Procedimento: public Simbolo
{
	private:
		vector<Parametro*> parametros;
	public:
		Procedimento(char*, int, TipoSimbolo);
		int getNumeroParametros();
		void adicionarParametro(Parametro*);
		Parametro getParametro(string);
};

#endif
