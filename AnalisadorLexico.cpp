#include "header/AnalisadorLexico.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char* palavrasReservadas[] = { "and", "begin", "boolean", "else", "end", "false", "function", "if", "integer", "mod", "not", "procedure", "program", "then", "true", "var", "while", ">", ">=", "<", "<=", "==", "=", "/", "*", "+", "-", ".", ",", ";", ":", "(", ")", "or"};

const int nPalavras   = 16;
const int nOperadores = 10;

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

TipoPedaco  AnalisadorLexico::proximoPedaco(bool consuma)
{
	if (!temMaisPedacos())
		return (TipoPedaco)fimDeArquivo;

	int i = 0;
	char* s = (char*)malloc(100*sizeof(char));
	char  c = fgetc(arquivo);

	while (c == '\t' || c == ' ' || c == '\n')
	{
		c = fgetc(arquivo);
	}

	while (!(c == '\t' || c == ' ' || c == '\n' || c == ';' || c == EOF || i >= 99))
	{
		s[i] = c;
		c = fgetc(arquivo);
		i++;
	}
	s[i] = '\x0';

	if (consuma)
	{
		int size = strlen(s);
		for (int i = 1; i <= size; i++)
			ungetc(arquivo, s[size - i]);
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
