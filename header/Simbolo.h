#ifndef Simbolo_H
#define Simbolo_H

#include <vector>
#include <string>

using namespace std;

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
		Simbolo(char*, int);
		Simbolo();
};

class Parametro: public Simbolo
{
	private:
		TipoVar tipo;
	public:
		Parametro(char[256], int, TipoVar);
		TipoVar getTipo();
};


class Variavel: public Simbolo
{
	private:
		TipoVar tipo;
	public:
		Variavel(char[256], int, TipoVar);
		TipoVar getTipo();
};

class Funcao: public Simbolo
{
	private:
		TipoVar tipoDeRetorno;
		vector<Parametro*> parametros;
	public:
		Funcao(char[256], int, TipoVar);
		int getNumeroParametros();
		void adicionarParametro(Parametro*);
		TipoVar getTipoDeRetorno();
};

class Procedimento: public Simbolo
{
	private:
		vector<Parametro*> parametros;
	public:
		Procedimento(char*, int);
		int getNumeroParametros();
		void adicionarParametro(Parametro*);
		Parametro getParametro(string);
};

#endif
