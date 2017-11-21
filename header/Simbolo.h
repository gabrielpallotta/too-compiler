#ifndef Simbolo_H
#define Simbolo_H

#include <vector>

using namespace std;

typedef enum
{
    inteiro,
    booleano
} Tipo;

class Simbolo
{
	private:
		char nome [256];
		unsigned char nivel;
};

class Parametro: public Simbolo
{
	private:
		Tipo tipo;
	public:
		Parametro(Tipo);
		Tipo getTipo();
};


class Variavel: public Simbolo
{
	private:
		Tipo tipo;
	public:
		Variavel(Tipo);
		Tipo getTipo();
};

class Funcao: public Simbolo
{
	private:
		Tipo tipoDeRetorno;
		vector<Parametro> parametros;
	public:
		Funcao(Tipo);
		int getNumeroParametros();
		Tipo getTipoDeRetorno();
};

class Procedimento: public Simbolo
{
	private:
		vector<Parametro> parametros;
	public:
		int getNumeroParametros();
		void adicionarParametro(Parametro);
};

#endif
