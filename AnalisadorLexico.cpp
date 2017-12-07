#include "header/AnalisadorLexico.h"
#include "header/Simbolo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char* palavrasReservadas[] = { "and", "begin", "boolean", "else", "end", "false", "function", "if", "integer", "mod", "not", "procedure", "program", "then", "true", "var", "while", "do", ">", ">=", "<", "<=", "=", ":=", "/", "*", "+", "-", ".", ",", ";", ":", "(", ")", "or", "<>"};

const int nPalavras   = 17;
const int nOperadores = 18;

AnalisadorLexico::AnalisadorLexico (char* nomeArq)
{
	this->arquivo = fopen(nomeArq, "r");
}

int AnalisadorLexico::temMaisPedacos()
{
	if (feof(arquivo))
			return 0;

	char c = fgetc(arquivo);
	while (c == '\t' || c == ' ' || c == '\n')
  	{
      c = fgetc(arquivo);
          if (feof(arquivo))
              return 0;
  	}

  ungetc(c, arquivo);
	return 1;
}

int QualOTipo(char* palavra) //busca sequencial pelos operadores e palavras
{
    int i = 0;
    for (; i < nPalavras + nOperadores - 1; i++)
    {
        int comparacao = strcmp(palavrasReservadas[i], palavra);
        if (comparacao == 0)
        {
            return i;
        }
    }
    return -1;
}

TipoPedaco AnalisadorLexico::proximoPedaco(bool consuma)
{
	if (!temMaisPedacos())
		return (TipoPedaco)fimDeArquivo;

	int i = 0;
	char* s = (char*)malloc(100*sizeof(char));
	char  c = fgetc(arquivo);

 	if (c == ';' || c == ':' || c == '+' || c == '-' || c == '*' || c == '/' || c == '{' || c == '}' || c == '(' || c == ')' || c == '>' || c == '<' || c == ',' || c == '.')
	{ //Se o primeiro caracter a ser lido for um desses, assume-se que a leitura é de uma expressão de variáveis coladas Ex.: a+b (não a + b)
		s[0] = tolower(c);
		c = fgetc(arquivo);

		if ( c == '=' ) // então é comparador >=, <=, ou :=
		{
            s[1] = tolower(c);
            s[2] = '\x0';
		}
		else
        {
            s[1] = '\x0';
            ungetc(c, arquivo);
        }

        if (!consuma)
        {
            int size = strlen(s);
            for (int i = 1; i <= size; i++)
                ungetc(s[size - i], arquivo);
        }

		i = QualOTipo(s);
		return static_cast<TipoPedaco>(i);
	}

	while (c == '\t' || c == ' ' || c == '\n')
	{
		c = fgetc(arquivo);
	}

	while (!(c == '\t' || c == ' ' || c == '\n' || c == ';' || c == ':' || c == '+' || c == '-' || c == '*' || c == '/' || c == '{' || c == '}' || c == '(' || c == ')' || c == '>' || c == '<' || c == ',' || c == '.' || c == EOF || i >= 99))
	{
		s[i] = tolower(c);
		c = fgetc(arquivo);
		i++;
	}
	ungetc(c, arquivo);
	s[i] = '\x0';

	if (!consuma)
	{
		int size = strlen(s);
		for (int i = 1; i <= size; i++)
			ungetc(s[size - i], arquivo);
	}

	i = QualOTipo(s);

	if (i > 0)
	{
		return static_cast<TipoPedaco>(i);   //retorna um TipoPedaco
                                         //com o mesmo indice
                                         //do vetor de palavras
	}
	else
	{
		int i = 1;
		if (isdigit(s[0]))
		{
			for(;i<strlen(s);i++)
				if (!isdigit(s[i]))
				{
                    return (TipoPedaco)desconhecido;
				}
                ultimoValor = atoi(s);
                return (TipoPedaco)numero;
		}
		else
		{
			ultimoIdentificador = s;
			return (TipoPedaco)identificador;
		}
	}
}

char* AnalisadorLexico::getNome()
{
	return ultimoIdentificador;
}

int AnalisadorLexico::getValor()
{
	return ultimoValor;
}

void AnalisadorLexico::desconsumirPedaco()
{
    char* s = getNome();
    int size = strlen(s);
    for (int i = 1; i <= size; i++)
        ungetc(s[size - i], arquivo);
}
