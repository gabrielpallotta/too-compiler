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
    var_booleano,
    var_void
} TipoVar;

class Simbolo
{
	public:
		char* nome;
		unsigned char nivel;
		TipoSimbolo tiposimb;
		TipoVar tipo;
		Simbolo(char*, int, TipoVar, TipoSimbolo);
		Simbolo();
};

class Variavel: public Simbolo
{
	public:
		Variavel(char*, int, TipoVar, TipoSimbolo);
};

class Metodo: public Simbolo
{
	private:
		vector<Variavel*> parametros;
	public:
		Metodo(char*, int, TipoVar, TipoSimbolo);
		int getNumeroParametros();
		void adicionarParametro(Variavel*);
		Variavel* getParametro (int i);
		TipoVar getTipoDeRetorno();
};

#endif
