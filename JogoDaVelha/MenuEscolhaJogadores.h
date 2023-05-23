#pragma once
#include "Menu.h"

class MenuEscolhaJogadores: protected Menu {
    public:
         MenuEscolhaJogadores(int corMenuInicial,MCUFRIEND_kbv* ptrTela, bool estadoBotao, const char* tituloMenuInicial):
    	Menu(corMenuInicial, ptrTela, estadoBotao, tituloMenuInicial)
    	{
    		criaBotoes();
    	}
        void criaBotoes(){
        Coordenada tamanhoBotao, posicaoBotao,posicaoCursor;

        tamanhoBotao = setCoord(180,90);

        //Botão 1 JOGADOR
        posicaoBotao = setCoord(70, 100);
        posicaoCursor = setCoord(105, 135);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "1 JOGADOR", true);
        listaBotoes[0] = ptrBotao;

        //Botão 2 JOGADORES
        posicaoBotao = setCoord(70,220);
        posicaoCursor = setCoord(95,255);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "2 JOGADORES", true);
        listaBotoes[1] = ptrBotao;

        posicaoBotao = setCoord(70,340);
        posicaoCursor = setCoord(130,375);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "VOLTAR", true);
        listaBotoes[2] = ptrBotao;
    }

    void desenharMenu(){
    	ptrTela->fillScreen(BLACK);
    	ptrTela->setCursor(30, 50);
    	ptrTela->setTextColor(WHITE);
    	ptrTela->setTextSize(2);
    	ptrTela->println(tituloMenu);

    	for(int i=0; i<3; i++)
    		listaBotoes[i]->desenharBotao();
    }
    void ligaBotao(int i){
        listaBotoes[i]->setCor(GREEN);
        listaBotoes[i]->desenharBotao();
    }
    
};
