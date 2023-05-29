#ifndef _JOGO_2D_
#define _JOGO_2D_
#include "Botao.h"
#include "stdafx.h"

class Jogo2D{
    private:
        int ativo;
        Botao* pause;
        int vetorPossibilidades[10];
        Botao* ptrBotao;
        
        
    public:
        Botao* hashBotao[10];
        Botao* JogodaVelha[3][3];
        Jogo2D(){
          tft.fillScreen(WHITE);
          criarBotoes();
          pause->desenharBotao();
          for (int i = 0; i < 9; i++){
              hashBotao[i]->desenharBotaoJogo();                            
            
          }
        }
        ~Jogo2D(){
              pause = nullptr;
        }
        void setAtivo(int index){
          ativo = index;
        }

        void criarBotoes(){
          Coordenada tamanhoBotao, posicaoBotao, posicaoCursor;
          tamanhoBotao = setCoord(90,45);
          posicaoBotao = setCoord(205,25);
          posicaoCursor = setCoord(220,40);
          pause = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, RED,"PAUSE",true, 2, 9,WHITE);
          hashBotao[9] = pause;
          tamanhoBotao = setCoord(90,90);
          
          posicaoBotao = setCoord(33,112);
          posicaoCursor = setCoord(53,122);
          ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,0, WHITE);
          hashBotao[0] = ptrBotao;
          JogodaVelha[0][0] = ptrBotao;
          posicaoBotao = setCoord(118,112);
          posicaoCursor = setCoord(138,122);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,1, WHITE);
          hashBotao[1]=ptrBotao;
          JogodaVelha[0][1] = ptrBotao;
          posicaoBotao = setCoord(203,112);
          posicaoCursor = setCoord(223,122);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,2, WHITE);
          hashBotao[2]=ptrBotao;
          JogodaVelha[0][2] = ptrBotao;
          posicaoBotao = setCoord(33,197);
          posicaoCursor = setCoord(53,207);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,3, WHITE);
          hashBotao[3]=ptrBotao;
          JogodaVelha[1][0] = ptrBotao;
          posicaoBotao = setCoord(118,197);
          posicaoCursor = setCoord(138,207);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,4, WHITE);
          hashBotao[4]=ptrBotao;
          JogodaVelha[1][1] = ptrBotao;
          posicaoBotao = setCoord(203,197);
          posicaoCursor = setCoord(223,207);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,5, WHITE);
          hashBotao[5]=ptrBotao;
          JogodaVelha[1][2] = ptrBotao;
          posicaoBotao = setCoord(33,282);
          posicaoCursor = setCoord(53,292);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,6, WHITE);
          hashBotao[6]=ptrBotao;
          JogodaVelha[2][0] = ptrBotao;
          posicaoBotao = setCoord(118,282);
          posicaoCursor = setCoord(138,292);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,7, WHITE);
          hashBotao[7]=ptrBotao;
          JogodaVelha[2][1] = ptrBotao;
          posicaoBotao = setCoord(203,282);
          posicaoCursor = setCoord(223,292);
           ptrBotao = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, BLACK,"", false,10,8, WHITE);
          hashBotao[8]=ptrBotao;
          JogodaVelha[2][2] = ptrBotao;
   
        }
      void DesenhaHash(){
        tft.fillScreen(WHITE);
        pause->desenharBotao();
        for (int i = 0; i < 3 ; i++){
          for(int j = 0; j < 3; j++){
            JogodaVelha[i][j]->desenharBotaoJogo();
            JogodaVelha[i][j]->setJogada(hash[i][j]); 
          }
        }
      }
      
      void zeraHash(){
        for(int i = 0; i < 9 ; i++){
          hashBotao[i]->setText();
        }
      }

      int getAtivo(){
        for(int i = 0; i < 10; i++){
            if(hashBotao[i]->ativo())
              return hashBotao[i]->getID();
        }
      }
    
      Coordenada getCoords(){
        Coordenada coord;
        if(pause->ativo()){
          coord.x = -1;
          coord.y = -1;
        }
        else{
          for(int i = 0; i <3 ; i++){
            for(int j = 0; j < 3; j++){
              if(JogodaVelha[i][j]->ativo()){
                coord.y = i;
                coord.x = j;
              }
            }
          }
        }
        return coord;        
      }      

      
      void setSelecionado(int input){
          int ativo = getAtivo();          
          if (input == 1){//esquerda
            if(ativo == 0 || ativo == 3 || ativo == 6){
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              //desenha ele
              hashBotao[ativo + 2]->setAtivo(true);
              hashBotao[ativo + 2]->desenhaJogadaSelecionada();
              //desenha ele
            }
            else if(ativo == 9){}
            else{
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              //desenha ele
              hashBotao[ativo - 1]->setAtivo(true);
              hashBotao[ativo - 1]->desenhaJogadaSelecionada();
              //desenha ele
            }
          }
          else if(input == 2){//cima
            if(ativo == 0 || ativo == 1 || ativo == 2){
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              //desenha ele
              hashBotao[9]->setAtivo(true);
              hashBotao[9]->desenhaSelecionado();
              //desenha ele
            }
            else if (ativo == 9){}
            else{
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              //desenha ele
              hashBotao[ativo - 3]->setAtivo(true);
              hashBotao[ativo - 3]->desenhaJogadaSelecionada();
              //desenha ele              
            }
          }
          else if (input == 3){//baixo
            if(ativo == 6 || ativo == 7 || ativo == 8){
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              //desenha ele dnv
              hashBotao[ativo - 6]->setAtivo(true);
              hashBotao[ativo - 6]->desenhaJogadaSelecionada();
              //desenha pause
            }
            else if(ativo == 9){
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->retiraSelecionado();
              //desenha ele
              hashBotao[0]->setAtivo(true);
              hashBotao[0]->desenhaJogadaSelecionada();
              //desenha ele
            }
            else{
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              //desenha ele
              hashBotao[ativo + 3]->setAtivo(true);
              hashBotao[ativo + 3]->desenhaJogadaSelecionada();
              //desenha ele
            }
          }
          else if(input == 4){// direita
            if(ativo == 2 || ativo == 5 || ativo == 8){
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              //desenha botao
              hashBotao[ativo - 2]->setAtivo(true);
              hashBotao[ativo - 2]->desenhaJogadaSelecionada();
              //desenha Botao
            }
            else if(ativo == 9){}
            else{
              hashBotao[ativo]->setAtivo(false);
              hashBotao[ativo]->desenhaJogadaSelecionada();
              hashBotao[ativo + 1]->setAtivo(true);
              hashBotao[ativo + 1]->desenhaJogadaSelecionada();
            }
          }
          delay(100);
        }
        
};
#endif