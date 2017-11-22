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
        throw new string ("Esperado 'program' no início do programa.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declaração do programa.");
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
        throw new string ("Esperado 'var' na declaração de variável.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
            throw new string ("Esperado identificador na declaração de variável.");

    prox = analex.proximoPedaco(true);

    while (prox == identificador)
    {
        prox = analex.proximoPedaco(true);

        vector<string> variaveis = vector<string>();;

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true)
            if (prox != virgula)
                throw new string ("Esperado ',' após declaração de variável.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado identificador após vírgula na declaração de variável.");
            
            // Guarda no vetor de variáveis a variável atual
            variaveis.push_back(analex.getValor());
        }

        prox = analex.proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw new string ("Esperado tipo de variável (inteiro ou booleano) após sua declaração.");
        
        TipoVar var;
        
        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < variaveis.length; i++)
        {
            tabela.guarde(new Variavel(variaveis[i], nivelAtual, var));
        }

        prox = analex.proximoPedaco(false);
    }
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento();
{
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != procedimento)
        throw new string ("Esperado 'procedure' na declaração de procedimento.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declaração de procedimento.");

    
    prox = analex.proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' na declaração de procedimento.");

    
}

void AnalisadorSintatico::compilaDeclaracaoDeFuncao();
{
    nivelAtual++;
    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != funcao)
        throw new string ("Esperado 'function' na declaração de função.");
    
    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declaração de função.");

    string nomeFuncao = getNome();

    prox = analex.proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' na declaração de função.");

    prox = analex.proximoPedaco(true);
    
    while (prox == identificador && prox != fechaParenteses)
    {
        vector<string> parametros = vector<string>();
        prox = analex.proximoPedaco(true);

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true);
            if (prox != virgula)
                throw new string ("Esperado ',' após declaração de parâmetro na declaração de função.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado identificador após vírgula na declaração de função.");
            
            // Guarda no vetor de parâmetros o parâmetro atual
            parametros.push_back(analex.getValor());

            prox = analex.proximoPedaco(false);
        }
        
        prox = analex.proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw new string ("Esperado tipo de parâmetro (inteiro ou booleano) após sua declaração.");
        
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
        throw new string ("Esperado ':' após declaração de parâmetros.");

    prox = analex.proximoPedaco(true);
    if (prox != inteiro && prox != booleano)
        throw new string ("Esperado tipo de retorno (inteiro ou booleano) após declaração de função.");

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

