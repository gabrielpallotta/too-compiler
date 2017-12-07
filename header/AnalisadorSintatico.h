#ifndef AnalisadorSintatico_H
#define AnalisadorSintatico_H

#include "AnalisadorLexico.h"
#include "TabelaDeSimbolos.h"

class AnalisadorSintatico
{
	private:
		AnalisadorLexico* analex;
		TabelaDeSimbolos* tabela;
	public:
	    AnalisadorSintatico(char*);
		void compilaInicioDePrograma();
	    void compilaProgramaPrincipal();
	    void compilaDeclaracaoDeVariavel();
	    void compilaDeclaracaoDeProcedimento();
	    void compilaDeclaracaoDeFuncao();

	    void compilaMetodo();

	    void compilaSe();
	    void compilaEnquanto();

	    void compilaComando();
	    void compilaComandoComposto();

	    void compilaAtribuicao();

	    void compilaExpressaoAritmetica();
	    void compilaTermo();
	    void compilaFator();

	    void compilaExpressaoRelacional();
	    void compilaTermoRelacional();
	    void compilaFatorRelacional();

	    void compilaExpressaoLogica();
};

#endif
