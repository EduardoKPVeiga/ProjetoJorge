/*
* Define um botão
*/

#pragma once
#include "stdafx.h"

class Botao{
	Coordenada posicaoBotao, tamanhoBotao, posicaoCursor;
	MCUFRIEND_kbv* ptrTela;
	int corBotao;
	char mensagemBotao[20];
	bool estadoBotao;
  int text_size;

public:
	Botao(){}

	Botao(Coordenada _posicaoBotao, Coordenada _tamanhoBotao, Coordenada _posicaoCursor, MCUFRIEND_kbv* _ptrTela, int _corBotao = WHITE, const char* _mensagemBotao = "", bool _estadoBotao = false, int size = 2):
		posicaoBotao(_posicaoBotao),
		tamanhoBotao(_tamanhoBotao),
		posicaoCursor(_posicaoCursor),
		ptrTela(_ptrTela),
		corBotao(_corBotao),
		estadoBotao(_estadoBotao),
    text_size(size)
		{
			strncpy(mensagemBotao, _mensagemBotao, 20);
		}
	~Botao(){}

    Coordenada getPosicaoBotao(){
    	return posicaoBotao;
    }

    void setTamanhoBotao(Coordenada _tamanhoBotao){
    	tamanhoBotao = _tamanhoBotao;
	}

    Coordenada getTamanhoBotao()
    {
    	return tamanhoBotao;
    }

    void setCor(int _corBotao){
    	corBotao = _corBotao;
    }

    //Método para desenhar um botão na tela
    void desenharBotao(){ 
      //superior esquerda
        ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y - 10, 20, 20, BLUE);
        ptrTela->fillRect(posicaoBotao.x - 5, posicaoBotao.y - 5, 20, 20, BLACK);
      //inferior direita 
        ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y + tamanhoBotao.y + 10, -20, -20, BLUE);
        ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 5, posicaoBotao.y + tamanhoBotao.y + 5, -20, -20, BLACK);
      //superior direita ok
        ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y - 10, -20, 20, BLUE);
        ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 5, posicaoBotao.y - 5, -20, 20, BLACK);
      //inferior esquerda
        ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y + tamanhoBotao.y + 10, 20, -20, BLUE);
        ptrTela->fillRect(posicaoBotao.x - 5, posicaoBotao.y + tamanhoBotao.y + 5, 20, -20, BLACK);
        
        ptrTela->fillRect(posicaoBotao.x, posicaoBotao.y, tamanhoBotao.x,tamanhoBotao.y, corBotao);
        ptrTela->setCursor(posicaoCursor.x,posicaoCursor.y);
        ptrTela->setTextColor(BLACK);
        ptrTela->setTextSize(text_size);
        ptrTela->println(mensagemBotao);
    }
};