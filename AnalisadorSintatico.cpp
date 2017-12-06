#include "header/AnalisadorSintatico.h"
#include "header/AnalisadorLexico.h"

#include "header/Simbolo.h"
#include <stdexcept>
#include <iostream>

using namespace std;

AnalisadorSintatico::AnalisadorSintatico(char* arquivo)
{
    analex = new AnalisadorLexico(arquivo);
    tabela = new TabelaDeSimbolos();
}

void AnalisadorSintatico::compilaInicioDePrograma()
{
    tabela->adicioneNivel();

    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != programa)
        throw runtime_error ("Esperado 'program' no inicio do programa.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado identificador na declaracao do programa.");

    prox = analex->proximoPedaco(true);
    if (prox != pontoVirgula)
        throw runtime_error ("Esperado ';' na declaracao de programa.");

    prox = analex->proximoPedaco(false);

    while (prox != comeco)
    {
        if (prox == variavel)
            compilaDeclaracaoDeVariavel();
        else if (prox == procedimento)
            compilaDeclaracaoDeProcedimento();
        else if (prox == funcao)
            compilaDeclaracaoDeFuncao();

        prox = analex->proximoPedaco(false);
    }

    compilaProgramaPrincipal();
}

void AnalisadorSintatico::compilaProgramaPrincipal()
{
    compilaComandoComposto();

    TipoPedaco prox = analex->proximoPedaco(true);
    if(prox != ponto)
        throw runtime_error ("Esperado '.' no fim do programa.");

}
void AnalisadorSintatico::compilaDeclaracaoDeVariavel()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != variavel)
        throw runtime_error ("Esperado 'var' na declaracao de variavel.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado nome de variavel na declarcao.");

    while (prox == identificador)
    {
        vector<char*> variaveis;

		variaveis.push_back(analex->getNome());

        prox = analex->proximoPedaco(true);
        while (prox != doisPontos)
        {
            if (prox != virgula)
                throw runtime_error ("Esperado ',' apos declaracao de variavel.");

            prox = analex->proximoPedaco(true);
            if (prox != identificador)
                throw runtime_error ("Esperado identificador apos virgula na declarcao de variavel.");

            // Guarda no vetor de variaveis a variavel atual

            variaveis.push_back( analex->getNome());

            prox = analex->proximoPedaco(true);
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw runtime_error ("Esperado tipo de variavel (inteiro ou booleano) apos sua declaracao.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < variaveis.size(); i++)
        {
            Simbolo* simb = tabela->getSimbolo(variaveis[i]);

            if (simb != NULL && simb->nivel == tabela->nivelAtual)
                throw runtime_error ("Redeclaracao de variavel ja declarada.");

            tabela->guarde(new Variavel(variaveis[i], tabela->nivelAtual, var, simb_variavel));
        }


        prox = analex->proximoPedaco(false);
    }
    prox = analex->proximoPedaco(true);
        if (prox != pontoVirgula)
            throw runtime_error ("Esperado ';' na declaracao de programa.");
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento()
{
    vector<char*> nomeParametros;
    vector<Variavel*> parametros;

    nomeParametros = vector<char*>();
    parametros = vector<Variavel*>();

    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != procedimento)
        throw runtime_error ("Esperado 'procedure' na declaracao de procedimento.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado nome do procedimento na declaracao.");

    Metodo* proc = new Metodo(analex->getNome(), tabela->nivelAtual, var_void, simb_procedimento);

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' na declaracao de procedimento.");

    blocoDeVariaveis:

    prox = analex->proximoPedaco(true);

    if (prox == variavel)
        prox = analex->proximoPedaco(true);

    if (prox != identificador && prox != fechaParenteses)
        throw runtime_error ("Esperado parametro ou ')' na declaracao de procedimento.");

    while (prox == identificador)
    {
		nomeParametros.push_back(analex->getNome());

        prox = analex->proximoPedaco(true);
        while (prox != doisPontos)
        {
            if (prox != virgula)
                throw runtime_error ("Esperado ',' para separar parametro.");

            prox = analex->proximoPedaco(true);

            if (prox == variavel)
                prox = analex->proximoPedaco(true);

            if (prox != identificador)
                throw runtime_error ("Esperado parametro na declaracao de procedimento.");

            nomeParametros.push_back(analex->getNome());

            prox = analex->proximoPedaco(true);
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw runtime_error ("Esperado tipo de variavel (inteiro ou booleano) apos sua declaracao.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < nomeParametros.size(); i++)
            parametros.push_back(new Variavel(nomeParametros[i], tabela->nivelAtual, var, simb_parametro));

        prox = analex->proximoPedaco(true);

        if (prox == pontoVirgula)
            goto blocoDeVariaveis;

        if (prox != virgula && prox != fechaParenteses)
            throw runtime_error ("Esperado ',' ou ')' na declaracao de procedimento.");

        prox = analex->proximoPedaco(true);

        if (prox == variavel)
            prox = analex->proximoPedaco(true);

        if (prox != identificador && prox != pontoVirgula)
            throw runtime_error ("Esperado identificador ou ';' na declaracao de procedimento.");
    }

    for (int i = 0; i < parametros.size(); i++)
        proc->adicionarParametro(parametros[i]);

    tabela->guarde(proc);
    tabela->adicioneNivel();

    for (int i = 0; i < parametros.size(); i++)
    {
        Simbolo* simb = tabela->getSimbolo(nomeParametros[i]);

        if (simb != NULL && simb->nivel == tabela->nivelAtual)
            throw runtime_error ("Parametro com mesmo nome de variavel ja declarada.");

        tabela->guarde(parametros[i]);
    }


    prox = analex->proximoPedaco(false);

    while (prox != comeco)
    {
        if (prox == variavel)
            compilaDeclaracaoDeVariavel();
        else if (prox == procedimento)
            compilaDeclaracaoDeProcedimento();
        else if (prox == funcao)
            compilaDeclaracaoDeFuncao();

        prox = analex->proximoPedaco(false);
    }

    compilaComandoComposto();

    tabela->elimineNivel();
}

void AnalisadorSintatico::compilaDeclaracaoDeFuncao()
{
    vector<char*> nomeParametros;
    vector<Variavel*> parametros;

    nomeParametros = vector<char*>();
    parametros = vector<Variavel*>();

    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != funcao)
        throw runtime_error ("Esperado 'function' na declaracao de funcao.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado nome do funcao na declaracao.");

    char* nomeFuncao = analex->getNome();

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' na declaracao de funcao.");

    prox = analex->proximoPedaco(true);

    if (prox == variavel)
        prox = analex->proximoPedaco(true);

    if (prox != identificador && prox != fechaParenteses)
        throw runtime_error ("Esperado parametro ou ')' na declaracao de funcao.");

    while (prox == identificador)
    {
		nomeParametros.push_back(analex->getNome());

        prox = analex->proximoPedaco(true);
        while (prox != doisPontos)
        {
            if (prox != virgula)
                throw runtime_error ("Esperado ',' para separar parametro.");

            prox = analex->proximoPedaco(true);

            if (prox == variavel)
                prox = analex->proximoPedaco(true);

            if (prox != identificador)
                throw runtime_error ("Esperado parametro na declaracao de procedimento.");

            nomeParametros.push_back(analex->getNome());

            prox = analex->proximoPedaco(true);
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw runtime_error ("Esperado tipo de retorno (inteiro ou booleano) da funcao");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < nomeParametros.size(); i++)
            parametros.push_back(new Variavel(nomeParametros[i], tabela->nivelAtual, var, simb_parametro));

        prox = analex->proximoPedaco(true);

        if (prox != pontoVirgula && prox != fechaParenteses)
            throw runtime_error ("Esperado ';' ou ')' na declaracao de procedimento.");

        prox = analex->proximoPedaco(true);

        if (prox == variavel)
            prox = analex->proximoPedaco(true);

        if (prox != identificador && prox != doisPontos)
            throw runtime_error ("Esperado identificador ou ':' na declaracao de procedimento");
    }

    prox = analex->proximoPedaco(true);
    if (prox != inteiro && prox != booleano)
        throw runtime_error ("Esperado tipo de retorno (inteiro ou booleano) apos declaracao de funcao.");

    TipoVar ret;

    if (prox == inteiro)
        ret = var_inteiro;
    else
        ret = var_booleano;

    Metodo* func = new Metodo(nomeFuncao, tabela->nivelAtual, ret, simb_funcao);

    for (int i = 0; i < parametros.size(); i++)
        func->adicionarParametro(parametros[i]);

    tabela->guarde(func);
    tabela->adicioneNivel();

    for (int i = 0; i < parametros.size(); i++)
    {
        Simbolo* simb = tabela->getSimbolo(nomeParametros[i]);

        if (simb != NULL && simb->nivel == tabela->nivelAtual)
            throw runtime_error ("Parametro com mesmo nome de variavel ja declarada.");

        tabela->guarde(parametros[i]);
    }

    prox = analex->proximoPedaco(false);

    while (prox != comeco)
    {
        if (prox == variavel)
            compilaDeclaracaoDeVariavel();
        else if (prox == procedimento)
            compilaDeclaracaoDeProcedimento();
        else if (prox == funcao)
            compilaDeclaracaoDeFuncao();

        prox = analex->proximoPedaco(false);
    }

    compilaComandoComposto();

    tabela->elimineNivel();
}


void AnalisadorSintatico::compilaProcedimento()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado identificador na chamada de procedimento.");

    Metodo* proc = (Metodo*)tabela->getSimbolo(analex->getNome());

    if (proc == 0)
        throw runtime_error ("Identificador inesperado");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' apos chamada de procedimento");

    while (prox == identificador)
    {
        Variavel* param = proc->getParametro(analex->getNome());
        if (param == 0 || tabela->getSimbolo(analex->getNome())->tiposimb != param->tiposimb)
            throw runtime_error ("Parametro invalido na chamada de procedimento");

        prox = analex->proximoPedaco(true);
        if (prox != virgula)
            throw runtime_error ("Esperado ',' para separarar parametros na chamada de procedimento.");

        prox = analex->proximoPedaco(true);
    }

    prox = analex->proximoPedaco(true);
    if (prox != fechaParenteses && prox != identificador)
        throw runtime_error ("Esperado ')' ou identificador na chamada de procedimento");

    prox = analex->proximoPedaco(true);
    if (prox != pontoVirgula)
        throw runtime_error ("Esperado ';' na declaracao de programa.");
}

void AnalisadorSintatico::compilaFuncao()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado identificador na chamada de funcao.");

    Metodo* func = (Metodo*)tabela->getSimbolo(analex->getNome());

    if (func == 0)
        throw runtime_error ("Identificador inesperado");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' apos chamada de funcao");

    while (prox == identificador)
    {
        Variavel* param = func->getParametro(analex->getNome());
        if (param == 0 || tabela->getSimbolo(analex->getNome())->tiposimb != param->tiposimb)
            throw runtime_error ("Parametro invalido na chamada de funcao");

        prox = analex->proximoPedaco(true);
        if (prox != virgula)
            throw runtime_error ("Esperado ',' para separarar parametros na chamada de funcao.");

        prox = analex->proximoPedaco(true);
    }

    prox = analex->proximoPedaco(true);
    if (prox != fechaParenteses && prox != identificador)
        throw runtime_error ("Esperado ')' ou identificador na chamada de funcao");

    prox = analex->proximoPedaco(true);
    if (prox != pontoVirgula)
        throw runtime_error ("Esperado ';' na declaracao de programa.");
}


void AnalisadorSintatico::compilaSe()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != se)
        throw new runtime_error ("Esperado 'if'.");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw new runtime_error ("Esperado '(' apos 'if'.");

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
                throw runtime_error ("Esperado ')' no fim da condicao.");
            else
                break;
        }
    }

    prox = analex->proximoPedaco(true);
    if (prox != entao)
        throw runtime_error ("Esperado 'Then' no fim da condicao.");

    prox = analex->proximoPedaco(true);
    if (prox == comeco)
    {
        compilaComandoComposto();
        prox = analex->proximoPedaco(true);

        if (prox == pontoVirgula)
        {
            prox = analex->proximoPedaco(false);
            if (prox == senao)
                throw runtime_error ("';' inesperado antes de 'Else'.");
        }
    }
    else
    {
        compilaComando();
        prox = analex->proximoPedaco(true);
        if (prox == pontoVirgula)
        {
            prox = analex->proximoPedaco(false);
            if (prox == senao)
                throw runtime_error ("';' inesperado antes de 'Else'.");
        }
        else if (prox == senao)
        {
            prox = analex->proximoPedaco(true);
            if (prox == comeco)
                compilaComandoComposto();
            else
                compilaComando();
        }
    }
}

void AnalisadorSintatico::compilaEnquanto()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != enquanto)
        throw runtime_error ("Esperado 'while'.");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' apos 'while'.");

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
                throw runtime_error ("Esperado ')' no fim da condicao.");
            else
                break;
        }
    }
}


void AnalisadorSintatico::compilaComando()
{
    TipoPedaco prox = analex->proximoPedaco(false);
    if (prox != identificador)
    {
      if (prox == enquanto)
        compilaEnquanto();
      else if (prox == se)
        compilaSe();
      else if (prox == inteiro || prox == booleano)
        compilaDeclaracaoDeVariavel();
      else if (prox == funcao)
        compilaDeclaracaoDeFuncao();
      else if (prox == procedimento)
        compilaDeclaracaoDeProcedimento();
      else
        throw runtime_error ("Comando desconhecido.");
    }
    else
    {
      Simbolo* s = tabela->getSimbolo(analex->getNome());

      if (s->tiposimb == simb_variavel || s->tiposimb == simb_parametro)
        compilaAtribuicao();
      else if (s->tiposimb == simb_funcao)
        compilaFuncao();
      else if (s->tiposimb == simb_procedimento)
        compilaProcedimento();
      else
        throw runtime_error ("Identificador inválido.");
    }
}

void AnalisadorSintatico::compilaComandoComposto()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != comeco)
        throw runtime_error ("Esperado 'begin' no inicio de comando composto.");

    prox = analex->proximoPedaco(false);

    while (prox != fim && analex->temMaisPedacos())
    {
        compilaComando();
        prox = analex->proximoPedaco(true);
    }

    if (!analex->temMaisPedacos())
        throw runtime_error ("Esperado 'end' no final de comando composto.");

    prox = analex->proximoPedaco(true);
    if (prox != pontoVirgula)
        throw runtime_error ("Esperado ';' na declaracao de comando composto.");
}


void AnalisadorSintatico::compilaAtribuicao()
{
    TipoPedaco prox = analex->proximoPedaco(true);

    if (prox != identificador)
        throw runtime_error ("Esperado identificador.");

    Simbolo* s = tabela->getSimbolo(analex->getNome());
        if (s->tiposimb != simb_variavel && s->tiposimb != simb_parametro)
            throw runtime_error ("Variavel/Parametro nao existe.");

    prox = analex->proximoPedaco(true);
    if (prox != atribuicao)
        throw runtime_error ("Esperado ':=' em atribuicao.");

    if (s->tiposimb == simb_variavel)
    {
        if(((Variavel*)s)->tipo == var_inteiro)
            compilaExpressaoAritmetica();
        else
            compilaExpressaoLogica();
    }
    else if(((Variavel*)s)->tipo == var_inteiro)
        compilaExpressaoAritmetica();
    else
        compilaExpressaoLogica();

    prox = analex->proximoPedaco(true);
    if (prox != pontoVirgula)
        throw runtime_error ("Esperado ';' na declaracao de programa.");

}


void AnalisadorSintatico::compilaExpressaoAritmetica()
{
    compilaTermo();
    TipoPedaco prox = analex->proximoPedaco(false);
    while(prox == mais || prox == menos)
    {
        analex->proximoPedaco(true);
        compilaTermo();
    }
}

void AnalisadorSintatico::compilaTermo()
{
    compilaFator();
    TipoPedaco prox = analex->proximoPedaco(false);
    while(prox == vezes || prox == dividido || prox == resto)
    {
        compilaFator();
        prox = analex->proximoPedaco(false);
    }
}

void AnalisadorSintatico::compilaFator()
{
    TipoPedaco prox = analex->proximoPedaco(true);

    if (prox == menos)
        prox = analex->proximoPedaco(true);

    if (prox == identificador)
    {
        Simbolo* s = tabela->getSimbolo(analex->getNome());

        if (s->tiposimb == simb_funcao)
        {
            Metodo* f = (Metodo*)s;

            if (f->tipo != var_inteiro)
                throw runtime_error ("Funcao nao retorna um inteiro.");

            compilaFuncao();
        }
        else if (!(s->tiposimb != simb_variavel) || ((Metodo*)s)->tipo != var_inteiro)
            throw runtime_error ("Funcao deve retornar inteiro no fator.");
        else
        {
            Simbolo* s = tabela->getSimbolo(analex->getNome());
            if (s->tiposimb != simb_variavel && s->tiposimb != simb_parametro)
                throw runtime_error ("Variavel nao existe.");

            if (s->tipo != var_inteiro)
                throw runtime_error ("Variavel nao eh inteira.");
        }
    }
    else
    {
        if (prox == abreParenteses)
        {
            compilaExpressaoAritmetica();
            prox = analex->proximoPedaco(true);
            if (prox != fechaParenteses)
                throw runtime_error ("Esperado ')' ao final de uma expressao aritmetica.");
        }
        else
            if (prox != numero)
                throw runtime_error ("Esperado numero.");
    }
}


void AnalisadorSintatico::compilaExpressaoRelacional()
{
    compilaExpressaoAritmetica();

    TipoPedaco prox = analex->proximoPedaco(true);
    if(prox != menor && prox != maior && prox != maiorIgual && prox != menorIgual && prox != igual && prox != diferente)
        throw runtime_error ("Esperado comparador na expressao relacional");

    compilaExpressaoAritmetica();
}

void AnalisadorSintatico::compilaTermoRelacional()
{
    compilaFatorRelacional();
    TipoPedaco prox;
    while(analex->proximoPedaco(false) == e)
    {
        prox = analex->proximoPedaco(true);
        compilaFatorRelacional();
    }
}

void AnalisadorSintatico::compilaFatorRelacional()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if(prox == nao)
        prox = analex->proximoPedaco(true);
    if(prox == identificador)
    {
        Simbolo* s = tabela->getSimbolo(analex->getNome());
        if(s->tiposimb == simb_funcao && ((Metodo*)s)->tipo == var_booleano)
            compilaFuncao();
        else if(!(s->tiposimb == simb_variavel) || !(((Variavel*)s)->tipo == var_booleano))
            compilaExpressaoRelacional();
    }
    else if (prox == abreParenteses)
    {
        compilaExpressaoLogica();
        prox = analex->proximoPedaco(true);
        if(prox != fechaParenteses)
            throw runtime_error ("Esperado ')' no fator relacional");
    }
    else if(prox != verdadeiro && prox != falso)
        throw runtime_error ("Esperado identificador booleano no fator relacional");
}


void AnalisadorSintatico::compilaExpressaoLogica()
{
    TipoPedaco prox = analex->proximoPedaco(false);

    if (!(prox == identificador || prox == numero || prox == verdadeiro || prox == falso))
        throw runtime_error ("Esperado identificador ou valor");

    if (prox == identificador)
        if (tabela->getSimbolo(analex->getNome()) == NULL)
            throw runtime_error ("Identificador nao existe");

    TipoVar tv = tabela->getSimbolo(analex->getNome())->tipo;

    if (prox == verdadeiro || prox == falso || tv == var_booleano)
    {
        prox = analex->proximoPedaco(true);
        prox = analex->proximoPedaco(false);

        if (prox == fechaParenteses)
            return;
        if (prox != igual && prox != diferente)
            throw runtime_error ("Comparação inesperada relativa de tipos booleanos");

        prox = analex->proximoPedaco(true);
        prox = analex->proximoPedaco(true);

        if (!(prox == verdadeiro || prox == falso || tabela->getSimbolo(analex->getNome())->tipo == var_booleano))
            throw runtime_error("Tipos incompativeis");
    }
    else
        compilaExpressaoRelacional();
}
