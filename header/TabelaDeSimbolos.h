#ifndef TabelaDeSimbolos_H
#define TabelaDeSimbolos_H

#include "header/Simbolo.h"
#include <vector>
#include <stack>

using namespace std;

class TabelaDeSimbolos
{
	private:
		vector<vector<Simbolo*> > listaDeSimbolos;
	    stack<char*> nomes;
	public:
	    int nivelAtual;
		TabelaDeSimbolos();
		void guarde (Simbolo*);
		void elimineNivel ();
		void adicioneNivel (char*);
		Simbolo* getSimbolo (char*);
		char* getNomeNivel();
};
	// estrutura armazenando simbolos;
  // metodo guarde();
  // metodo elimineNivel(int n);

	//Busca-se nomes e faz-se a correspondência (verificação de parâmetros e existência)
	//Ex.: Atribuindo valor, verifica-se se o tipo é compatível.
	//		X Proc1 := 5 + 9 	X
	//		X a = b(c);			X

	//Estrutura armazandando símbolos a serem buscados.
	//(Método get. Estrutura de dados)

	//guardaNivel()
	//elimineNivel()

	// Ex.:
	//
	// Program prog
	// var a, b, c : integer;
	// Procedure Proc1;
	// 	var d, e : integer;
	// 	Procedure Proc2;
	// 		var f, g : integer;
	// 		begin
	// 		 	//"a", "b", "c", "d", "e", "f" e "g" acessíveis. nível 2
	// 		end;
	// 	begin
	// 	 	//"a", "b", "c", "d" e "e" acessíveis. nivel 1
	// 	end;
	// begin
	//  	//"a", "b" e "c" acessíveis. nivel 0
	// end.

#endif
