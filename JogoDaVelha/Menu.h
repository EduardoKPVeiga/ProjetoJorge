/*
* Define um menu
*/

#pragma once
#include "Botao.h"

class Menu{
protected:
	int corMenu;
    MCUFRIEND_kbv* ptrTela;
    bool estadoDoMenu;
    Botao* listaBotoes[3];
    char tituloMenu[30];
    Botao* ptrBotao;
    int numBotoes;
public:
	Menu(){}

    Menu(int _corMenu, MCUFRIEND_kbv* _ptrTela, bool _estadoDoMenu, const char* _tituloMenu  = "",int quantBotoes = 0):
        corMenu(_corMenu),
        ptrTela(_ptrTela),
        estadoDoMenu(_estadoDoMenu),
        numBotoes(quantBotoes)      
        {   
            
            strncpy(tituloMenu, _tituloMenu, 30);
            ptrBotao = nullptr;
            for (int i = 0; i < 3; i++){
                listaBotoes[i] = nullptr;}
        }

        ~Menu(){
            ptrBotao = nullptr;
            free(listaBotoes);
        }

        void desenharMenu(){
          ptrTela->fillScreen(BLACK);
          ptrTela->setCursor(30, 50);
          ptrTela->setTextColor(YELLOW);
          ptrTela->setTextSize(2);
          ptrTela->println(tituloMenu);

          listaBotoes[0]->setAtivo(true);
          for(int i=1; i< numBotoes; i++)
            listaBotoes[i]->setAtivo(false);

          for(int i=0; i<numBotoes; i++){
            listaBotoes[i]->setCor(RED);
            listaBotoes[i]->desenharBotao();
          }
        }
        

        virtual void criaBotoes() = 0;


        void setEstadoDoMenu(bool _estadoDoMenu = false){
            estadoDoMenu = _estadoDoMenu;
        }

        /*retorna qual botao esta ativo*/
        int indexBotaoAtivo(){
          for(int i = 0; i < numBotoes; i++){
            if(listaBotoes[i]->ativo())
              return i;
          }
        }

        /*desenha lista de botoes*/
        void desenhaBotoes(){
          for(int i = 0; i < numBotoes; i++){
            listaBotoes[i]->desenharBotao();
          }
        }


        /*faz animação de troca de botoes*/
        void trocaBotao(int input){
          int i = indexBotaoAtivo();
          listaBotoes[i]->setAtivo(false);
          listaBotoes[i]->retiraSelecionado();
          if(input == 2){
            if(i == 0){
              listaBotoes[numBotoes-1]->setAtivo(true);
              listaBotoes[numBotoes-1]->desenhaSelecionado();
            }
            else{
              listaBotoes[i-1]->setAtivo(true);
              listaBotoes[i-1]->desenhaSelecionado();
            }
          }
          if(input == 3){
            if(i == (numBotoes-1)){
              listaBotoes[0]->setAtivo(true);
              listaBotoes[0]->desenhaSelecionado();
            }
            else{
              listaBotoes[i+1]->setAtivo(true);
              listaBotoes[i+1]->desenhaSelecionado();
            }
          }
        }
        void ligaBotao(int i){
          listaBotoes[i]->setCor(GREEN);
          listaBotoes[i]->desenharBotao();
       }
};