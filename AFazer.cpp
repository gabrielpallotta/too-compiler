typedef struct
{
	//...

} DadosDeFuncao;

typedef struct
{
	//...

} DadosDeParametro;

typedef struct
{
	//...

} DadosDeProcedimento;

typedef struct
{
	//...

} DadosDeValor;

typedef struct
{
	//...

} DadosDeVariavel;

//Tudo acima podem ser classes
//E a union abaixo pode ser uma classe "acima na hierarquia"

typedef union
{
	DadosDeFuncao
	DadosDeParametro
	DadosDeProcedimento
	DadosDeVariavel

} Dados;

// DadosDeFuncao
// DadosDeParametro
// DadosDeProcedimento
// DadosDeValor
// DadosDeVariavel

class Funcao: public Simbolo
{
	//...
}

class Parametro: public Simbolo
{
	//...
}

class Procedimento: public Simbolo
{
	//...
}

class Variavel: public Simbolo
{
	//...
}

class Simbolo
{

}

class TabelaDeSimbolos
{
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
}
