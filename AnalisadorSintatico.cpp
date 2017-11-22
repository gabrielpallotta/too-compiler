#include "header/AnalisadorSintatico.h"
#include "header/AnalisadorLexico.h"

using namespace std;

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
        throw new string ("Esperado 'program' no in?cio do programa.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declara??o do programa.");
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
        throw new string ("Esperado 'var' na declara??o de vari?vel.");

    prox = analex.proximoPedaco(false);

    if (prox != identificador)
        throw new string ("Esperado nome de vari?vel na declar??o.")

    while (prox == identificador)
    {
        prox = analex.proximoPedaco(true);

        vector<string> variaveis = vector<string>();
		variaveis.push_back(prox);

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true)
            if (prox != virgula)
                throw new string ("Esperado ',' ap?s declara??o de vari?vel.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado identificador ap?s v?rgula na declara??o de vari?vel.");

            // Guarda no vetor de vari?veis a vari?vel atual
            variaveis.push_back(analex.getNome());
        }

        prox = analex.proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw new string ("Esperado tipo de vari?vel (inteiro ou booleano) ap?s sua declara??o.");
        
        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < variaveis.length; i++)
            tabela.guarde(new Variavel(variaveis[i], nivelAtual, var));

        prox = analex.proximoPedaco(false);
    }
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento();
{
    nivelAtual++;

    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != procedimento)
        throw new string ("Esperado 'procedure' na declara??o de procedimento.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado nome do procedimento na declara??o.");

    Procedimento proc = new Procedimento(analex.getNome(), nivelAtual);

    prox = analex.proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' na declara??o de procedimento.");

    prox = analex.proximoPedaco(true);

    if (prox != identificador && prox != fechaParenteses)
        throw new string ("Esperado par?metro ou ')' na declara??o de procedimento.");

    while (prox == identificador)
    {
        vector<string> parametrosDeUmTipo = vector<string>();
		parametrosDeUmTipo.push_back(prox);

        prox = analex.proximoPedaco(true);

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true)
            if (prox != virgula)
                throw new string ("Esperado ',' para separar par?metro.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado par?metro na declara??o de proceimento.");

            // Guarda no vetor de vari?veis a vari?vel atual
            variaveis.push_back(analex.getNome());
        }

        prox = analex.proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
                throw new string ("Esperado tipo de vari?vel (inteiro ou booleano) ap?s sua declara??o.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < parametrosDeUmTipo.length; i++)
            proc.adicionarParametro(new Parametro(parametrosDeUmTipo[i], nivelAtual, var));

        prox = analex.proximoPedaco(true);

        if (prox != ',' && prox != ')')
            throw new string ("Esperado ',' ou ')' na declara??o de procedimento.");

        prox = analex.proximoPedaco(true);
    }

    tabela.guarde(procedimento);

    if (analex.proximoPedaco(false) == variavel)
        compilaDeclaracaoDeVariavel();

    compilaComandoComposto();

    nivelAtual--;
}

void AnalisadorSintatico::compilaDeclaracaoDeFuncao();
{
    nivelAtual++;
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != funcao)
        throw new string ("Esperado 'function' na declara??o de fun??o.");
    
    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declara??o de fun??o.");

    string nomeFuncao = getNome();

    prox = analex.proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' na declara??o de fun??o.");

    prox = analex.proximoPedaco(true);
    
    while (prox == identificador && prox != fechaParenteses)
    {
        vector<string> parametros = vector<string>();
        prox = analex.proximoPedaco(true);

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true);
            if (prox != virgula)
                throw new string ("Esperado ',' ap?s declara??o de par?metro na declara??o de fun??o.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado identificador ap?s v?rgula na declara??o de fun??o.");
            
            // Guarda no vetor de par?metros o par?metro atual
            parametros.push_back(analex.getValor());

            prox = analex.proximoPedaco(false);
        }
        
        prox = analex.proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw new string ("Esperado tipo de par?metro (inteiro ou booleano) ap?s sua declara??o.");
        
        TipoVar par;
        
        if (prox == inteiro)
            par = var_inteiro;
        else
            par = var_booleano;

        for (int i = 0; i < parametros.length; i++)
        {
            tabela.guarde(new Parametro(parametros[i], nivelAtual, par));
        }

        prox = analex.proximoPedaco(false);  
    }

    prox = analex.proximoPedaco(true);
    if (prox != doisPontos)
        throw new string ("Esperado ':' ap?s declara??o de par?metros.");

    prox = analex.proximoPedaco(true);
    if (prox != inteiro && prox != booleano)
        throw new string ("Esperado tipo de retorno (inteiro ou booleano) ap?s declara??o de fun??o.");

    if (prox == inteiro)
        TipoVar ret = var_inteiro;
    else
        TipoVar ret = var_booleano;

    Funcao funcao = new Funcao(nomeFuncao, nivelAtual, ret);

    for (int i = 0; i < parametros.length; i++)
    {
        funcao->adicionarParametro(parametros[i]);
    }
}


void AnalisadorSintatico::compilaProcedimento();
{
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na chamada de procedimento.");
    
    if (tabela.)
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
