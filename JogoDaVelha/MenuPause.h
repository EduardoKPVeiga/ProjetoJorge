/*
* Menu de pause
*/

#pragma once
#include "Menu.h"

class MenuPause : protected Menu{
	bool isMultiplayer;
public:
	MenuPause;

	MenuPause(int corMenuPausa, MCUFRIEND_kbv* ptrTela, bool estadoBotao, const char* tituloMenuPausa):
		Menu(corMenuPausa, ptrTela, estadoBotao, tituloMenuPausa),
		isMultiplayer(false)
		{
			criaBotoes();
		}

	void criaBotoes(){
        Coordenada tamanhoBotao, posicaoBotao, posicaoCursor;

        tamanhoBotao = setCoord(180,90);

        //Botão RETORNAR
        posicaoBotao = setCoord(70,100);
        posicaoCursor = setCoord(105,135);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "Retornar", true);
        listaBotoes[0] = ptrBotao;

        //Botão REINICIAR
        posicaoBotao = setCoord(70,220);
        posicaoCursor = setCoord(105,255);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "Reiniciar", true);
        listaBotoes[1] = ptrBotao;

        //Botão SAIR
        posicaoBotao = setCoord(70,340);
        posicaoCursor = setCoord(105,375);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "Sair", true);
        listaBotoes[2] = ptrBotao;
    }

    void desenharMenu(){
    	ptrTela->fillScreen(BLACK);
    	ptrTela->setCursor(30, 50);
    	ptrTela->setTextColor(WHITE);
    	ptrTela->setTextSize(3);
    	ptrTela->println(tituloMenu);

    	for(int i=0; i<3; i++)
    		listaBotoes[i]->desenharBotao();
    }
    void ligaBotao(int i){
        listaBotoes[i]->setCor(GREEN);
        listaBotoes[i]->desenharBotao();
    }    
};