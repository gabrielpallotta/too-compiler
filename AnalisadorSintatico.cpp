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
        throw runtime_error ("Esperado 'var' na declaracao de vari?vel.");

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

        cout << variaveis.size();
        for (int i = 0; i < variaveis.size(); i++)
        {
            tabela->guarde(new Variavel(variaveis[i], tabela->nivelAtual, var, simb_variavel));
        }


        prox = analex->proximoPedaco(false);
    }
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento()
{
    tabela->adicioneNivel();

    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != procedimento)
        throw runtime_error ("Esperado 'procedure' na declaracao de procedimento.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado nome do procedimento na declaracao.");

    Procedimento* proc = new Procedimento(analex->getNome(), tabela->nivelAtual, simb_procedimento);

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' na declaracao de procedimento.");

    prox = analex->proximoPedaco(true);

    if (prox != identificador && prox != fechaParenteses)
        throw runtime_error ("Esperado parametro ou ')' na declaracao de procedimento.");

    while (prox == identificador)
    {
        vector<char*> parametrosDeUmTipo = vector<char*>();
		parametrosDeUmTipo.push_back(analex->getNome());

        prox = analex->proximoPedaco(true);

        while (prox != doisPontos)
        {
            prox = analex->proximoPedaco(true);
            if (prox != virgula)
                throw runtime_error ("Esperado ',' para separar parametro.");

            prox = analex->proximoPedaco(true);
            if (prox != identificador)
                throw runtime_error ("Esperado parametro na declaracao de proceimento.");

            // Guarda no vetor de vari?veis a vari?vel atual
            parametrosDeUmTipo.push_back(analex->getNome());
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
                throw runtime_error ("Esperado tipo de variavel (inteiro ou booleano) apos sua declaracao.");

        TipoVar var;

        if (prox == inteiro)
            var = var_inteiro;
        else
            var = var_booleano;

        for (int i = 0; i < parametrosDeUmTipo.size(); i++)
            proc->adicionarParametro(new Parametro(parametrosDeUmTipo[i], tabela->nivelAtual, var, simb_parametro));

        prox = analex->proximoPedaco(true);

        if (prox != virgula && prox != fechaParenteses)
            throw runtime_error ("Esperado ',' ou ')' na declaracao de procedimento.");

        prox = analex->proximoPedaco(true);
    }

    tabela->guarde(proc);

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
    tabela->adicioneNivel();

    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != funcao)
        throw runtime_error ("Esperado 'function' na declaracao de funcao.");

    prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado identificador na declaracao de funcao.");

    char* nomeFuncao = analex->getNome();

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' na declaracao de funcao.");

    prox = analex->proximoPedaco(true);

    vector<char*> nomeParametros;
    vector<Parametro*> parametros;

    while (prox == identificador || prox == variavel && prox != fechaParenteses)
    {
        if (prox == variavel)
        prox = analex->proximoPedaco(true);

        parametros = vector<char*>();

        prox = analex->proximoPedaco(true);


        while (prox != doisPontos)
        {
            prox = analex->proximoPedaco(true);
            if (prox != abreParenteses)

            prox = analex->proximoPedaco(true);
            if (prox != virgula)
                throw runtime_error ("Esperado ',' apos declaracao de parametro na declaracao de funcao.");

            prox = analex->proximoPedaco(true);
            if (prox != identificador)
                throw runtime_error ("Esperado identificador apos virgula na declaracao de funcao.");

            // Guarda no vetor de par?metros o par?metro atual
            parametros.push_back(analex->getNome());

            prox = analex->proximoPedaco(false);
        }

        prox = analex->proximoPedaco(true);
        if (prox != inteiro && prox != booleano)
            throw runtime_error ("Esperado tipo de parametro (inteiro ou booleano) apos sua declaracao.");

        TipoVar par;

        if (prox == inteiro)
            par = var_inteiro;
        else
            par = var_booleano;

        for (int i = 0; i < parametros.size(); i++)
        {
            Parametro* p = new Parametro(parametros[i], tabela->nivelAtual, par, simb_parametro);
            tabela->guarde(p);
            parametros.push_back(p);
        }

        prox = analex->proximoPedaco(false);
    }

    prox = analex->proximoPedaco(true);
    if (prox != doisPontos)
        throw runtime_error ("Esperado ':' apos declaracao de parametros.");

    prox = analex->proximoPedaco(true);
    if (prox != inteiro && prox != booleano)
        throw runtime_error ("Esperado tipo de retorno (inteiro ou booleano) apos declaracao de funcao.");

    TipoVar ret;

    if (prox == inteiro)
        ret = var_inteiro;
    else
        ret = var_booleano;

    Funcao* funcao = new Funcao(nomeFuncao, tabela->nivelAtual, ret, simb_funcao);
    // CONSERTAR ISSO AQUI EU NAO SEI O QUE FAZER

    for (int i = 0; i < parametros.size(); i++)
        funcao->adicionarParametro(parametros[i]);

    tabela->guarde(funcao);
}


void AnalisadorSintatico::compilaProcedimento()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado identificador na chamada de procedimento.");

    Procedimento* proc = (Procedimento*)tabela->getSimbolo(analex->getNome());

    if (proc == 0)
        throw runtime_error ("Identificador inesperado");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' apos chamada de procedimento");

    while (prox == identificador)
    {
        Parametro* param = proc->getParametro(analex->getNome());
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


}

void AnalisadorSintatico::compilaFuncao()
{
    TipoPedaco prox = analex->proximoPedaco(true);
    if (prox != identificador)
        throw runtime_error ("Esperado identificador na chamada de funcao.");

    Funcao* func = (Funcao*)tabela->getSimbolo(analex->getNome());

    if (func == 0)
        throw runtime_error ("Identificador inesperado");

    prox = analex->proximoPedaco(true);
    if (prox != abreParenteses)
        throw runtime_error ("Esperado '(' apos chamada de funcao");

    while (prox == identificador)
    {
        Parametro* param = func->getParametro(analex->getNome());
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
    if (prox != doisPontos)
        throw runtime_error ("Esperado ':' antes de '=' em atribuicao.");

    prox = analex->proximoPedaco(true);
    if (prox != igual)
        throw runtime_error ("Esperado '=' depois de ':' em atribuicao.");

    if (s->tiposimb == simb_variavel)
    {
        if(((Variavel*)s)->getTipo() == var_inteiro)
            compilaExpressaoAritmetica();
        else
            compilaExpressaoLogica();
    }
    else if(((Parametro*)s)->getTipo() == var_inteiro)
        compilaExpressaoAritmetica();
    else
        compilaExpressaoLogica();


}


void AnalisadorSintatico::compilaExpressaoAritmetica()
{
    compilaTermo();
    while(analex->proximoPedaco(false) == mais || analex->proximoPedaco(false) == menos)
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
        prox = analex->proximoPedaco(true);
        compilaFator();
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
            Funcao* f = (Funcao*)s;

            if (f->getTipoDeRetorno() != var_inteiro)
                throw runtime_error ("Funcao nao retorna um inteiro.");

            compilaFuncao();
        }
        else if (!(s->tiposimb != simb_variavel) || ((Funcao*)s)->getTipoDeRetorno() != var_inteiro)
            throw runtime_error ("Funcao deve retornar inteiro no fator.");
        else
        {
            Simbolo* s = tabela->getSimbolo(analex->getNome());
            if (s->tiposimb != simb_variavel)
                throw runtime_error ("Variavel nao existe.");

            Variavel* v = (Variavel*)s;

            if (v->getTipo() != var_inteiro)
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
        if(s->tiposimb == simb_funcao && ((Funcao*)s)->getTipoDeRetorno() == var_booleano)
            compilaFuncao();
        else if(!(s->tiposimb == simb_variavel) || !(((Variavel*)s)->getTipo() == var_booleano))
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
    TipoPedaco prox = analex->proximoPedaco(true);

    if (!(prox == identificador || prox == numero))             //verificar a validade dos identificadores os valores
        throw runtime_error ("Esperado identificador ou valor");

    if (prox == identificador)
        if (tabela->getSimbolo(analex->getNome()) == nullptr)
            throw runtime_error ("Identificador nao existe");

    TipoVar tv = tabela->getSimbolo(analex->getNome())->TipoVar;

    if (prox == verdadeiro || prox == falso || tv == var_booleano)
    {
        prox = analex->proximoPedaco(false);
        if (prox == fechaParenteses)
            return;
    }

    prox = analex->proximoPedaco(true);
    if (!(prox == igual || prox == menor || prox == menorIgual || prox == maior || prox == maiorIgual || prox == diferente))
        throw runtime_error ("Esperado comparador");
    else if (tv == var_booleano)
    {
        if (!(prox == igual || prox == diferente))
            throw runtime_error ("Comparação inesperada relativa de tipos booleanos");
    }

    prox = analex->proximoPedaco(true);
    if (!(prox == identificador || prox == numero))
        throw runtime_error ("Esperado identificador ou valor");

    if (prox == identificador)
        if (tabela->getSimbolo(analex->getNome()) == nullptr)
            throw runtime_error ("Identificador nao existe");

    if (tv != tabela->getSimbolo(analex->getNome())->TipoVar)
        throw runtime_error ("Tipos incompatíveis na comparação.");
}
