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

    prox = analex.proximoPedaco(false);

    if (prox != identificador)
        throw new string ("Esperado nome de variável na declarção.")

    while (prox == identificador)
    {
        prox = analex.proximoPedaco(true);

        vector<string> variaveis = vector<string>();
		variaveis.push_back(prox);

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true)
            if (prox != virgula)
                throw new string ("Esperado ',' após declaração de variável.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado identificador após vírgula na declaração de variável.");

            // Guarda no vetor de variáveis a variável atual
            variaveis.push_back(analex.getNome());
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
            tabela.guarde(new Variavel(variaveis[i], nivelAtual, var));

        prox = analex.proximoPedaco(false);
    }
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento();
{
    nivelAtual++;

    TipoPedaco prox = analex.proximoPedaco(true);
    if (prox != procedimento)
        throw new string ("Esperado 'procedure' na declaração de procedimento.");

    prox = analex.proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado nome do procedimento na declaração.");

    Procedimento proc = new Procedimento(analex.getNome(), nivelAtual);

    prox = analex.proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' na declaração de procedimento.");

    prox = analex.proximoPedaco(true);

    if (prox != identificador && prox != fechaParenteses)
        throw new string ("Esperado parâmetro ou ')' na declaração de procedimento.");

    while (prox == identificador)
    {
        vector<string> parametrosDeUmTipo = vector<string>();
		parametrosDeUmTipo.push_back(prox);

        prox = analex.proximoPedaco(true);

        while (prox != doisPontos)
        {
            prox = analex.proximoPedaco(true)
            if (prox != virgula)
                throw new string ("Esperado ',' para separar parâmetro.");

            prox = analex.proximoPedaco(true)
            if (prox != identificador)
                throw new string ("Esperado parâmetro na declaração de proceimento.");

            // Guarda no vetor de variáveis a variável atual
            variaveis.push_back(analex.getNome());
        }

        prox = analex.proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
                throw new string ("Esperado tipo de variável (inteiro ou booleano) após sua declaração.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < parametrosDeUmTipo.length; i++)
            proc.adicionarParametro(new Parametro(parametrosDeUmTipo[i], nivelAtual, var));

        prox = analex.proximoPedaco(true);

        if (prox != ',' && prox != ')')
            throw new string ("Esperado ',' ou ')' na declaração de procedimento.");

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
