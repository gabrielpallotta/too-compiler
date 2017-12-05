#ifndef AnalisadorLexico_H
#define AnalisadorLexico_H

#include <stdio.h>
#include "header/Simbolo.h"

typedef enum {
	e,
	comeco,
	booleano,
	senao,
	fim,
	falso,
    funcao,
	se,
	inteiro,
	resto,
	nao,
    procedimento,
	programa,
	entao,
	verdadeiro,
	variavel,
	enquanto,
    maior,
    maiorIgual,
    menor,
    menorIgual,
	igual,
	atribuicao,
    dividido,
    vezes,
    mais,
    menos,
    ponto,
    virgula,
    pontoVirgula,
	doisPontos,
	abreParenteses,
	fechaParenteses,
	ou,
	diferente,
	desconhecido,
	identificador,
	numero,
	fimDeArquivo
} TipoPedaco;

extern const char* palavrasReservadas[];
extern const int nPalavras;
extern const int nOperadores;

class AnalisadorLexico
{
    public:
		AnalisadorLexico(char*);
		TipoPedaco proximoPedaco(bool);
		int        temMaisPedacos();
		char*      getNome();
		int        getValor();
	private:
		FILE* arquivo;
		char* ultimoIdentificador;
		int   ultimoValor;

};

#endif
