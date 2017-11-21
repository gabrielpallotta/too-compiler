#include "AnalisadorLexico.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

AnalisadorLexico::AnalisadorLexico (char* nomeArq)
{
	this->arquivo = fopen(nomeArq, "r");
}

int AnalisadorLexico::temMaisPedacos()
{
	char c = fgetc(arquivo);
	while (c == '\t' || c == ' ' || c == '\n')
    {
        c = fgetc(arquivo);
            if (c == EOF)
                return 0;
    }

    ungetc(c, arquivo);
	return 1;
}

int QualOTipo(char* palavra) //busca sequencial pelos operadores e palavras
{
    int i = nPalavras;
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

	char* s = (char*)malloc(100*sizeof(char));
	char  c = 'x';

	while (c != '\t' || c != ' ' || c != '\n' || c != EOF)
	{
	    c = fgetc(arquivo);
		s = strcat(s, &c);
	}

    if (!consuma)
        for (int i = 0; i < strlen(s); i++)
            ungetc(s[strlen(s) - i], arquivo);

	int i = QualOTipo(s);

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
