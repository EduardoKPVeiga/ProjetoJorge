#pragma once
#include "Menu.h"

class MenuEscolhaJogadores: public Menu {
    public:
    MenuEscolhaJogadores(int corMenuInicial,MCUFRIEND_kbv* ptrTela, bool estadoBotao, const char* tituloMenuInicial):
    	Menu(corMenuInicial, ptrTela, estadoBotao, tituloMenuInicial,3)
    	{
    		criaBotoes();
    	}
        void criaBotoes(){
        Coordenada tamanhoBotao, posicaoBotao,posicaoCursor;

        tamanhoBotao = setCoord(180,90);

        //Botão 1 JOGADOR
        posicaoBotao = setCoord(70, 100);
        posicaoCursor = setCoord(105, 135);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "1 JOGADOR", true, 2,0);
        listaBotoes[0] = ptrBotao;

        //Botão 2 JOGADORES
        posicaoBotao = setCoord(70,220);
        posicaoCursor = setCoord(95,255);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "2 JOGADORES", false,2, 1);
        listaBotoes[1] = ptrBotao;

        posicaoBotao = setCoord(70,340);
        posicaoCursor = setCoord(130,375);
        ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, ptrTela, RED, "VOLTAR", false,2, 2);
        listaBotoes[2] = ptrBotao;
    }    
};
