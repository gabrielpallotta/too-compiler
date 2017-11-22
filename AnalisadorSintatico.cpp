#include "header/AnalisadorSintatico.h"
#include "header/AnalisadorLexico.h"

void AnalisadorSintatico::AnalisadorSintatico()
{
    nivelAtual = 0;
    analex = new AnalisadorLexico();
    tabela = new TabelaDeSimbolos();
}

void AnalisadorSintatico::compilaInicioDePrograma()
{
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != programa)
        throw new string ("Esperado 'program' no in�cio do programa.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declara��o do programa.");
}

void AnalisadorSintatico::compilaProgramaPrincipal()
{
    nivelAtual++;

    compilaComandoComposto();

    TipoPedaco prox = analex.proximoPedaco(true);
    if(prox != ponto)
        throw new string ("Esperado '.' no fim do programa.");

}
void AnalisadorSintatico::compilaDeclaracaoDeVariavel();
{
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != variavel)
        throw new string ("Esperado 'var' na declara��o de vari�vel.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
            throw new string ("Esperado identificador na declara��o de vari�vel.");

    prox = analex.proximoPedaco(true);

    while (prox == identificador)
    {
        prox = analex.proximoPedaco(true);

        vector<string> variaveis = vector<string>();;

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true)
            if (prox != virgula)
                throw new string ("Esperado ',' ap�s declara��o de vari�vel.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado identificador ap�s v�rgula na declara��o de vari�vel.");

            // Guarda no vetor de vari�veis a vari�vel atual
            variaveis.push_back(analex.getValor());
        }

        prox = analex.proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
                throw new string ("Esperado tipo de vari�vel (inteiro ou booleano) ap�s sua declara��o.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < variaveis.length; i++)
        {
            tabela.guarde(new Variavel(variaveis[i], nivelAtual, var));
        }

        prox = analex.proximoPedaco(true);
    }
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento();
{
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != procedimento)
        throw new string ("Esperado 'procedure' na declara��o de procedimento.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declara��o de procedimento.");


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
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != se)
        throw new string ("Esperado 'if'.");
    
    prox = analex.proximoPedaco(true);
    if (prox != abreParenteses)    
        throw new string ("Esperado '(' após 'if'.");
    
    while (true)
    {
        compilaExpressaoLogica();
        prox = analex.proximoPedaco(true);
        if (prox == e || prox == ou)
            continue;
        else
        {
            prox = analex.proximoPedaco(true);
            if (prox != fechaParenteses)
                throw new string ("Esperado ')' no fim da condição.");
            else
                break;
        }
    }
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
    TipoPedaco prox = analex.proximoPedaco(true);

    if (!(prox == identificador || prox == numero))
        throw new string ("Esperado identificador ou valor");
    
    prox = analex.proximoPedaco(true);
    if (!(prox == igual || prox == menor || prox == menorIgual || prox == maior || prox == maiorIgual || prox == diferente))
        throw new string("Esperado comparador");
    
    prox = analex.proximoPedaco(true);
    if (!(prox == identificador || prox == numero))
        throw new string ("Esperado identificador ou valor");
}
