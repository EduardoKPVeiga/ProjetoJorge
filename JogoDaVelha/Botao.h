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
  int index;
  int corFundoAtivo;
  int corTexto;
public:
	Botao(){}

	Botao(Coordenada _posicaoBotao, Coordenada _tamanhoBotao, Coordenada _posicaoCursor, MCUFRIEND_kbv* _ptrTela, int _corBotao = WHITE, const char* _mensagemBotao = "", bool _estadoBotao = false, int size = 2, int i = 0,int corFundo = BLACK):
		posicaoBotao(_posicaoBotao),
		tamanhoBotao(_tamanhoBotao),
		posicaoCursor(_posicaoCursor),
		ptrTela(_ptrTela),
		corBotao(_corBotao),
		estadoBotao(_estadoBotao),
    text_size(size),
    index(i),
    corFundoAtivo(corFundo)
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
    int getID(){
      return index;
    }
    bool ativo(){
      if(estadoBotao)
        return true;
      return false;
    }

    void setAtivo(bool estado){
      estadoBotao = estado;
    }

    void desenhaSelecionado(){
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y - 10, 20, 5, BLUE);
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y - 10, 5, 10, BLUE);
    //inferior direita 
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y + tamanhoBotao.y + 10, -20, -5, BLUE);
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y + tamanhoBotao.y + 10, -5, -20, BLUE);
    //superior direita ok
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y - 10, -20, 5,BLUE);
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y - 10, -5, 20, BLUE);
    //inferior esquerda
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y + tamanhoBotao.y + 10, 20, -5, BLUE);
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y + tamanhoBotao.y + 10, 5, -20, BLUE);
    }
    void retiraSelecionado(){
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y - 10, 20, 5, corFundoAtivo);
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y - 10, 5, 10, corFundoAtivo);
    //inferior direita 
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y + tamanhoBotao.y + 10, -20, -5, corFundoAtivo);
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y + tamanhoBotao.y + 10, -5, -20, corFundoAtivo);
    //superior direita ok
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y - 10, -20, 5,corFundoAtivo);
      ptrTela->fillRect(posicaoBotao.x + tamanhoBotao.x + 10, posicaoBotao.y - 10, -5, 20, corFundoAtivo);
    //inferior esquerda
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y + tamanhoBotao.y + 10, 20, -5, corFundoAtivo);
      ptrTela->fillRect(posicaoBotao.x - 10, posicaoBotao.y + tamanhoBotao.y + 10, 5, -20, corFundoAtivo);

    }

    //Método para desenhar um botão na tela
    void desenharBotao(){ 
      //superior esquerda
      if(estadoBotao){
        desenhaSelecionado();
      }
      else{
        retiraSelecionado();
      }

      ptrTela->fillRect(posicaoBotao.x, posicaoBotao.y, tamanhoBotao.x,tamanhoBotao.y, corBotao);
      ptrTela->setCursor(posicaoCursor.x,posicaoCursor.y);
      ptrTela->setTextColor(BLACK);
      ptrTela->setTextSize(text_size);
      ptrTela->println(mensagemBotao);
    }
    void setJogada(int jogada){
      
      if(jogada == 1){
        ptrTela->setTextColor(BLUE);
        corTexto = BLUE;
        ptrTela->setTextSize(text_size,text_size);
        ptrTela->setCursor(posicaoCursor.x,posicaoCursor.y);
        ptrTela->println("X");
        mensagemBotao[0]='X';
      }
      else if(jogada == 2){
        ptrTela->setTextColor(RED);
        corTexto = RED;       
        ptrTela->setTextSize(text_size,text_size);
        ptrTela->setCursor(posicaoCursor.x,posicaoCursor.y);
        ptrTela->println("O");
        mensagemBotao[0]='O';
      }
    }

    void setText(){
      mensagemBotao[0]='\0';
    }
    void desenharBotaoJogo(){
      //superior esquerda
      ptrTela->fillRect(posicaoBotao.x, posicaoBotao.y, tamanhoBotao.x,tamanhoBotao.y, corBotao);
      desenhaJogadaSelecionada();
      ptrTela->fillRect(posicaoBotao.x+5, posicaoBotao.y+5, tamanhoBotao.x-10, tamanhoBotao.y-10, corFundoAtivo);
      ptrTela->setCursor(posicaoCursor.x,posicaoCursor.y);
      ptrTela->setTextColor(corTexto);
      ptrTela->setTextSize(text_size,text_size);
      ptrTela->println(mensagemBotao);
      
    }
    void desenhaJogadaSelecionada(){
      int cor;
      if(estadoBotao)
        cor = YELLOW;
      else
        cor = corFundoAtivo;      
      ptrTela->fillRect(posicaoBotao.x+5, posicaoBotao.y+5, tamanhoBotao.x-10, tamanhoBotao.y-10, cor);
      ptrTela->setCursor(posicaoCursor.x,posicaoCursor.y);
      ptrTela->setTextColor(corTexto);
      ptrTela->setTextSize(text_size,text_size);
      ptrTela->println(mensagemBotao);

    }

};
