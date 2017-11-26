#include "header/AnalisadorSintatico.h"
#include "header/AnalisadorLexico.h"

#include "header/Simbolo.h"

using namespace std;

AnalisadorSintatico::AnalisadorSintatico(char* arquivo)
{
    nivelAtual = 0;
    analex = new AnalisadorLexico(arquivo);
    tabela = new TabelaDeSimbolos();
}

void AnalisadorSintatico::compilaInicioDePrograma()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != programa)
        throw new string ("Esperado 'program' no inicio do programa.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declaracao do programa.");
}

void AnalisadorSintatico::compilaProgramaPrincipal()
{
    nivelAtual++;

    compilaComandoComposto();

    TipoPedaco prox = analex->proximoPedaco(true);
    if(prox != ponto)
        throw new string ("Esperado '.' no fim do programa.");

}
void AnalisadorSintatico::compilaDeclaracaoDeVariavel()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != variavel)
        throw new string ("Esperado 'var' na declaracao de vari?vel.");

    prox = analex->proximoPedaco(false);

    if (prox != identificador)
        throw new string ("Esperado nome de variavel na declarcao.");

    while (prox == identificador)
    {
        prox = analex->proximoPedaco(true);

        vector<char*> variaveis = vector<char*>();
		variaveis.push_back(analex->getNome());

        while (prox != doisPontos)
        {
            prox = analex->proximoPedaco(true);
            if (prox != virgula)
                throw new string ("Esperado ',' apos declaracao de variavel.");

            prox = analex->proximoPedaco(true);
            if (prox != identificador)
                throw new string ("Esperado identificador apos virgula na declarcao de variavel.");

            // Guarda no vetor de vari?veis a vari?vel atual
            variaveis.push_back(analex->getNome());
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw new string ("Esperado tipo de variavel (inteiro ou booleano) apos sua declaracao.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < variaveis.size(); i++)
            tabela->guarde(new Variavel(variaveis[i], nivelAtual, var));

        prox = analex->proximoPedaco(false);
    }
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento()
{
    nivelAtual++;

    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != procedimento)
        throw new string ("Esperado 'procedure' na declaracao de procedimento.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado nome do procedimento na declaracao.");

    Procedimento* proc = new Procedimento(analex->getNome(), nivelAtual);

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' na declaracao de procedimento.");

    prox = analex->proximoPedaco(true);

    if (prox != identificador && prox != fechaParenteses)
        throw new string ("Esperado parametro ou ')' na declaracao de procedimento.");

    while (prox == identificador)
    {
        vector<char*> parametrosDeUmTipo = vector<char*>();
		parametrosDeUmTipo.push_back(analex->getNome());

        prox = analex->proximoPedaco(true);

        while (prox != doisPontos)
        {
            prox = analex->proximoPedaco(true);
            if (prox != virgula)
                throw new string ("Esperado ',' para separar parametro.");

            prox = analex->proximoPedaco(true);
            if (prox != identificador)
                throw new string ("Esperado parametro na declaracao de proceimento.");

            // Guarda no vetor de vari?veis a vari?vel atual
            parametrosDeUmTipo.push_back(analex->getNome());
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
                throw new string ("Esperado tipo de vari?vel (inteiro ou booleano) apos sua declaracao.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < parametrosDeUmTipo.size(); i++)
            proc->adicionarParametro(new Parametro(parametrosDeUmTipo[i], nivelAtual, var));

        prox = analex->proximoPedaco(true);

        if (prox != ',' && prox != ')')
            throw new string ("Esperado ',' ou ')' na declaracao de procedimento.");

        prox = analex->proximoPedaco(true);
    }

    tabela->guarde(proc);

    if (analex->proximoPedaco(false) == variavel)
        compilaDeclaracaoDeVariavel();

    compilaComandoComposto();

    nivelAtual--;
}

void AnalisadorSintatico::compilaDeclaracaoDeFuncao()
{
    nivelAtual++;
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != funcao)
        throw new string ("Esperado 'function' na declaracao de funcao.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na declaracao de funcao.");

    char* nomeFuncao = analex->getNome();

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' na declaracao de funcao.");

    prox = analex->proximoPedaco(true);

    vector<char*> parametros;

    while (prox == identificador && prox != fechaParenteses)
    {
        parametros = vector<char*>();
        prox = analex->proximoPedaco(true);

        while (prox != doisPontos)
        {
            prox = analex->proximoPedaco(true);
            if (prox != virgula)
                throw new string ("Esperado ',' apos declaracao de parametro na declaracao de funcao.");

            prox = analex->proximoPedaco(true);
            if (prox != identificador)
                throw new string ("Esperado identificador apos virgula na declaracao de funcao.");

            // Guarda no vetor de par?metros o par?metro atual
            parametros.push_back(analex->getNome());

            prox = analex->proximoPedaco(false);
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw new string ("Esperado tipo de parametro (inteiro ou booleano) apos sua declaracao.");

        TipoVar par;

        if (prox == inteiro)
            par = var_inteiro;
        else
            par = var_booleano;

        for (int i = 0; i < parametros.size(); i++)
        {
            tabela->guarde(new Parametro(parametros[i], nivelAtual, par));
        }

        prox = analex->proximoPedaco(false);
    }

    prox = analex->proximoPedaco(true);
    if (prox != doisPontos)
        throw new string ("Esperado ':' apos declaracao de parametros.");

    prox = analex->proximoPedaco(true);
    if (prox != inteiro && prox != booleano)
        throw new string ("Esperado tipo de retorno (inteiro ou booleano) ap?s declaracao de funcao.");

    TipoVar ret;

    if (prox == inteiro)
        ret = var_inteiro;
    else
        ret = var_booleano;

    Funcao* funcao = new Funcao(nomeFuncao, nivelAtual, ret);

    // CONSERTAR ISSO AQUI EU NAO SEI O QUE FAZER

    //for (int i = 0; i < parametros.size(); i++)
    //{
    //funcao->adicionarParametro(new Parametro(parametros[i], );
    //}
}


void AnalisadorSintatico::compilaProcedimento()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na chamada de procedimento.");

    Procedimento* proc = (Procedimento)tabela->getSimbolo(analex->getNome(), nivelAtual);

    if (proc == null)
        throw new string ("Identificador inesperado");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' apos chamada de procedimento");

    while (prox == identificador)
    {
        Parametro param = proc.getParametro(analex.getNome());
        if (param == null || tabela.getSimbolo(analex.getNome()).tipoSimbolo != param.tipoSimbolo)
            throw new string ("Parametro invalido na chamada de procedimento");

        prox = analex->proximoPedaco(true);
        if (prox != virgula)
            throw new string ("Esperado ',' para separarar parametros na chamada de procedimento.");
        
        prox = analex->proximoPedaco(true);
    }

    prox = analex->proximoPedaco(true);
    if (prox != fechaParenteses && prox != identificador)
        throw new string ("Esperado ')' ou identificador na chamada de procedimento");

    
}

void AnalisadorSintatico::compilaFuncao()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw new string ("Esperado identificador na chamada de funcao.");

    Funcao* func = (Funcao)tabela->getSimbolo(analex->getNome(), nivelAtual);

    if (func == null)
        throw new string ("Identificador inesperado");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' apos chamada de funcao");

    while (prox == identificador)
    {
        Parametro param = func.getParametro(analex.getNome());
        if (param == null || tabela.getSimbolo(analex.getNome()).tipoSimbolo != param.tipoSimbolo)
            throw new string ("Parametro invalido na chamada de funcao");

        prox = analex->proximoPedaco(true);
        if (prox != virgula)
            throw new string ("Esperado ',' para separarar parametros na chamada de funcao.");
        
        prox = analex->proximoPedaco(true);
    }

    prox = analex->proximoPedaco(true);
    if (prox != fechaParenteses && prox != identificador)
        throw new string ("Esperado ')' ou identificador na chamada de funcao");
}


void AnalisadorSintatico::compilaSe()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != se)
        throw new string ("Esperado 'if'.");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' apos 'if'.");

    while (true)
    {
        compilaExpressaoLogica();
        prox = analex->proximoPedaco(true);
        if (prox == e || prox == ou)
            continue;
        else
        {
            prox = analex->proximoPedaco(true);
            if (prox != fechaParenteses)
                throw new string ("Esperado ')' no fim da condicao.");
            else
                break;
        }
    }
}

void AnalisadorSintatico::compilaEnquanto()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != enquanto)
        throw new string ("Esperado 'while'.");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw new string ("Esperado '(' apos 'while'.");

    while (true)
    {
        compilaExpressaoLogica();
        prox = analex->proximoPedaco(true);
        if (prox == e || prox == ou)
            continue;
        else
        {
            prox = analex->proximoPedaco(true);
            if (prox != fechaParenteses)
                throw new string ("Esperado ')' no fim da condicao.");
            else
                break;
        }
    }
}


void AnalisadorSintatico::compilaComando()
{

}

void AnalisadorSintatico::compilaComandoComposto()
{
    prox = analex->proximoPedaco(true);
    if (prox != inicio)
        throw new string ("Esperado 'begin' no inicio de comando composto.");

    prox = analex->proximeoPedaco(true);

    while (prox != fim && analex->temMaisPedacos())
    {
        compilaComando();
        prox = analex->proximoPedaco(true);
    }

    if (!analex->temMaisPedacos())
        throw new string ("Esperado 'end' no final de comando composto.");
}


void AnalisadorSintatico::compilaAtribuicao()
{

}


void AnalisadorSintatico::compilaExpressaoAritmetica()
{

}

void AnalisadorSintatico::compilaTermo()
{
    compilaFator();
    TipoPedaco prox = analex->proximoPedaco(false);
    while(prox == vezes || prox == dividido || prox == resto)
    {
        prox = analex->proximoPedaco(true);
        compilaFator();
    }
}

void AnalisadorSintatico::compilaFator()
{

}


void AnalisadorSintatico::compilaExpressaoRelacional()
{

}

void AnalisadorSintatico::compilaTermoRelacional()
{

}

void AnalisadorSintatico::compilaFatorRelacional()
{

}


void AnalisadorSintatico::compilaExpressaoLogica()
{
    TipoPedaco prox = analex->proximoPedaco(true);

    if (!(prox == identificador || prox == numero))             //verificar a validade dos identificadores os valores
        throw new string ("Esperado identificador ou valor");

    prox = analex->proximoPedaco(true);
    if (!(prox == igual || prox == menor || prox == menorIgual || prox == maior || prox == maiorIgual || prox == diferente))
        throw new string("Esperado comparador");

    prox = analex->proximoPedaco(true);
    if (!(prox == identificador || prox == numero))
        throw new string ("Esperado identificador ou valor");
}
