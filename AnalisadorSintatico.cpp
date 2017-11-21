#include "header/AnalisadorSintatico.h"
#include "header/AnalisadorLexico.h"

void AnalisadorSintatico::compilaInicioDePrograma()
{
    prox = analex.proximoPedaco(true);

    if (prox != programa)
        throw new string ()
}

void AnalisadorSintatico::compilaProgramaPrincipal()
{
    compilaComandoComposto();
    prox = analex.proximoPedaco(true);
    if(prox != ponto)
        throw new string ("Esperado '.' no fim do programa");

}
void AnalisadorSintatico::compilaDeclaracaoDeVariavel();
{
    prox = analex.proximoPedaco(true);

    if (prox != variavel)


}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento();
{

}

void AnalisadorSintatico::compilaDeclaracaoDeFuncao();
{

}


void AnalisadorSintatico::compilaProcedimento();
{

}

void AnalisadorSintatico::compilaFuncao();
{

}


void AnalisadorSintatico::compilaSe();
{

}

void AnalisadorSintatico::compilaEnquanto();
{

}


void AnalisadorSintatico::compilaComando();
{

}

void AnalisadorSintatico::compilaComandoComposto();
{

}


void AnalisadorSintatico::compilaAtribuicao();
{

}


void AnalisadorSintatico::compilaExpressaoAritmetica();
{

}

void AnalisadorSintatico::compilaTermo();
{

}

void AnalisadorSintatico::compilaFator();
{

}


void AnalisadorSintatico::compilaExpressaoRelacional();
{

}

void AnalisadorSintatico::compilaTermoRelacional();
{

}

void AnalisadorSintatico::compilaFatorRelacional();
{

}


void AnalisadorSintatico::compilaExpressaoLogica();
{

}

