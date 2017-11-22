#ifndef Simbolo_H
#define Simbolo_H

#include <vector>

using namespace std;

typedef enum
{
    var_inteiro,
    var_booleano
} TipoVar;

class Simbolo
{
	private:
		char nome [256];
		unsigned char nivel;
	public:
		Simbolo(char[256], int);
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
		vector<Parametro> parametros;
	public:
		Funcao(char[256], int, TipoVar);
		int getNumeroParametros();
		TipoVar getTipoDeRetorno();
};

class Procedimento: public Simbolo
{
	private:
		vector<Parametro> parametros;
	public:
		Procedimento(char[256], int);
		int getNumeroParametros();
		void adicionarParametro(Parametro);
};

#endif
