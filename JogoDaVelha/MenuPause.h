/*
* Menu de pause
*/

#pragma once
#include "Menu.h"

class MenuPause : public Menu{
	bool isMultiplayer;
public:
	MenuPause;

	MenuPause(int corMenuPausa, MCUFRIEND_kbv* ptrTela, bool estadoBotao, const char* tituloMenuPausa):
		Menu(corMenuPausa, ptrTela, estadoBotao, tituloMenuPausa, 3),
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
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "Retornar", true,2, 0);
        listaBotoes[0] = ptrBotao;

        //Botão REINICIAR
        posicaoBotao = setCoord(70,220);
        posicaoCursor = setCoord(105,255);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "Reiniciar", false,2, 1);
        listaBotoes[1] = ptrBotao;

        //Botão SAIR
        posicaoBotao = setCoord(70,340);
        posicaoCursor = setCoord(105,375);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "Sair", false,2,2);
        listaBotoes[2] = ptrBotao;
    }  
};