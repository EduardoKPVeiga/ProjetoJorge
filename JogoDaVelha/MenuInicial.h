/*
* Menu inicial
*/

#pragma once
#include "Menu.h"

class MenuInicial : protected Menu{
public:
	~MenuInicial(){}

	MenuInicial(int corMenuInicial,MCUFRIEND_kbv* ptrTela, bool estadoBotao, const char* tituloMenuInicial):
    	Menu(corMenuInicial, ptrTela, estadoBotao, tituloMenuInicial)
    	{
    		criaBotoes();
    	}

    void criaBotoes(){
        Coordenada tamanhoBotao, posicaoBotao,posicaoCursor;

        tamanhoBotao = setCoord(180,90);

        //Botão 1 JOGADOR
        posicaoBotao = setCoord(70,120);
        posicaoCursor = setCoord(100,155);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "JOGO 2D", true, 3);
        listaBotoes[0] = ptrBotao;

        //Botão 2 JOGADORES
        posicaoBotao = setCoord(70,240);
        posicaoCursor = setCoord(100,275);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "JOGO 3D", true, 3);
        listaBotoes[1] = ptrBotao;
    }

    void desenharMenu(){
    	ptrTela->fillScreen(BLACK);
    	ptrTela->setCursor(30, 50);
    	ptrTela->setTextColor(WHITE);
    	ptrTela->setTextSize(2);
    	ptrTela->println(tituloMenu);

    	for(int i=0; i<2; i++)
    		listaBotoes[i]->desenharBotao();
    }
    
    void ligaBotao(int i){
        listaBotoes[i]->setCor(GREEN);
        listaBotoes[i]->desenharBotao();
    }
};