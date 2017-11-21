#ifndef AnalisadorLexico_H
#define AnalisadorLexico_H

#include <stdio.h>

typedef enum {
	e,
	comeco,
	boleano,
	senao,
	fim,
	falso,
    funcao,
	se,
	inteiro,
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
    igualIgual,
    igual,
    barra,
    asterisco,
    mais,
    menos,
    ponto,
    pontoVirgula,
    doisPontos,
	desconhecido,
	identificador,
	numero,
	fimDeArquivo
} TipoPedaco;

const char* palavrasReservadas[] = { "and", "begin", "boolean", "else", "end", "false", "function", "if", "integer", "not", "procedure", "program", "then", "true", "var", "while", ">", ">=", "<", "<=", "==", "=", "/", "*", "+", "-", ".", ";", ":"};

const int nPalavras   = 16;
const int nOperadores = 10;

class AnalisadorLexico
{
    public:
		AnalisadorLexico(char*);
		TipoPedaco proximoPedaco(FILE*);
		int        temMaisPedacos();
		char*      getNome();
		int        getValor();

	private:
		FILE* arquivo;
		char* ultimoIdentificador;
		int   ultimoValor;

};

#endif
