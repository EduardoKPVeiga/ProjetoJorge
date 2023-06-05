#ifndef _JOGO_3D_
#define _JOGO_3D_
#include "stdafx.h"
#include"Botao.h"
class Jogo3D{
    private:
      int ativo;
    public:
      quadradoHash3D* hashTresD[3][3][3];
      Botao* pause;
      Jogo3D(){
        Coordenada tamanhoBotao, posicaoBotao, posicaoCursor;
        tamanhoBotao = setCoord(90,45);
        posicaoBotao = setCoord(205,25);
        posicaoCursor = setCoord(220,40);
        pause = new Botao(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, RED,"PAUSE",false, 2, 9,BLACK);
        criaObjetos();
        pause->desenharBotaoJogo();
      }
      
      ~Jogo3D(){
        pause = NULL;
      }
      void criaObjetos(){
        quadradoHash3D* q;
        for(int k = 0; k < 3; k++){
          for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
              q = new quadradoHash3D();
              q->ativo = false;
              q->type = 0;
              hashTresD[k][i][j] = q;
            }
          }
        }
        hashTresD[0][0][0]->ativo = true;
        LigaDesligaPosicao(0,0,0);
        int e = 3;
        hashTresD[0][0][0]->inicio = setCoord(50 + e, 69 + e);
        hashTresD[0][0][1]->inicio = setCoord(96+ 2 + e, 69 + e);
        hashTresD[0][0][2]->inicio = setCoord(144 + e, 69 + e);
        hashTresD[0][1][0]->inicio = setCoord(76 + e , 108 + e);
        hashTresD[0][1][1]->inicio = setCoord(122 +10 + e, 108 + e);
        hashTresD[0][1][2]->inicio = setCoord(170 + e, 108 + e);
        hashTresD[0][2][0]->inicio = setCoord(103 + e , 146 + e);
        hashTresD[0][2][1]->inicio = setCoord(149 + e , 146 + e);
        hashTresD[0][2][2]->inicio = setCoord(197 + e , 146 + e);
        hashTresD[1][0][0]->inicio = setCoord(50 + e, 205 + e);
        hashTresD[1][0][1]->inicio = setCoord(96 + e, 205 + e);
        hashTresD[1][0][2]->inicio = setCoord(144 + e, 205 + e);
        hashTresD[1][1][0]->inicio = setCoord(76 + e ,244 + e);
        hashTresD[1][1][1]->inicio = setCoord(122 + e,244 + e);
        hashTresD[1][1][2]->inicio = setCoord(170 + e,244 + e);
        hashTresD[1][2][0]->inicio = setCoord(103 + e ,282 + e);
        hashTresD[1][2][1]->inicio = setCoord(149 + e ,282 + e);
        hashTresD[1][2][2]->inicio = setCoord(197 + e ,282 + e);
        hashTresD[2][0][0]->inicio = setCoord(50 + e, 341 + e);
        hashTresD[2][0][1]->inicio = setCoord(96 + e, 341 + e);
        hashTresD[2][0][2]->inicio = setCoord(144 + e, 341 + e);
        hashTresD[2][1][0]->inicio = setCoord(76 + e , 380 + e);
        hashTresD[2][1][1]->inicio = setCoord(122 + e, 380 + e);
        hashTresD[2][1][2]->inicio = setCoord(170 + e, 380 + e);
        hashTresD[2][2][0]->inicio = setCoord(103 + e , 418 + e);
        hashTresD[2][2][1]->inicio = setCoord(149 + e , 418 + e);
        hashTresD[2][2][2]->inicio = setCoord(197 + e , 418 + e);
      }

      void desenhaHash(){               
        limparTela(tft);
        int y_padrao_const = 69;
        int x_padrao = 50;
        int y_padrao = 69;
        int largura = 140;
        int espessura = -10;
        int alturaTriangulo = 116;
        int larguraTriangulo = 80; 
        int distanciasMalhas = 20;
        //horizontais da malha 1
        tft.fillRect(x_padrao,y_padrao,largura,3,WHITE);
        tft.fillRect(x_padrao + 80, y_padrao + 116, largura, 10, WHITE);
        tft.fillRect(x_padrao + 26, y_padrao + 39 , largura, 3, WHITE);
        tft.fillRect(x_padrao + 53, y_padrao + 77 , largura, 3, WHITE);

        //diagonais da malha 1
        for(int i = 0; i > espessura; i--){
            desenharDiagonal( tft, x_padrao + larguraTriangulo , y_padrao + alturaTriangulo - i, x_padrao, y_padrao - i, false, WHITE, 1);
        }
        desenharDiagonal(tft, x_padrao + largura, y_padrao, x_padrao + 219, y_padrao + alturaTriangulo,false, WHITE,3);
        desenharDiagonal(tft, x_padrao + 46, y_padrao, x_padrao + 126, y_padrao + alturaTriangulo,true, WHITE,3);
        desenharDiagonal(tft, x_padrao + 94, y_padrao, x_padrao + 174, y_padrao + alturaTriangulo,true, WHITE,3);



        y_padrao += (alturaTriangulo + distanciasMalhas);
        
        //horizontais da malha 2
        tft.fillRect(x_padrao,y_padrao,largura,3,WHITE);
        tft.fillRect(x_padrao + larguraTriangulo, y_padrao + alturaTriangulo, largura, 10, WHITE);
        tft.fillRect(x_padrao + 26, y_padrao + 39 , largura , 3, WHITE);
        tft.fillRect(x_padrao + 53, y_padrao + 77 , largura, 3, WHITE);

        //diagonais da malha 2
        for(int i = 0; i > espessura; i--){
            desenharDiagonal( tft, x_padrao + larguraTriangulo, y_padrao + alturaTriangulo - i, x_padrao, y_padrao - i, false, WHITE, 1);
        }
        desenharDiagonal(tft, x_padrao + largura, y_padrao, x_padrao + 219, y_padrao + alturaTriangulo,false, WHITE,3);
        desenharDiagonal(tft, x_padrao + 46, y_padrao, x_padrao + 126, y_padrao + alturaTriangulo,true, WHITE,3);
        desenharDiagonal(tft, x_padrao + 94, y_padrao, x_padrao + 174, y_padrao + alturaTriangulo,true, WHITE,3);

        y_padrao += (116+20);

        //horizontais da malha 3
        tft.fillRect(x_padrao,y_padrao,largura,3,WHITE);
        tft.fillRect(x_padrao + 80, y_padrao + 116, largura, 10, WHITE);
        tft.fillRect(x_padrao + 26, y_padrao + 39 , largura , 3, WHITE);
        tft.fillRect(x_padrao + 53, y_padrao + 77 , largura , 3, WHITE);
        //diagonais da malha 3
        for(int i = 0; i > espessura; i--){
            desenharDiagonal( tft, x_padrao + 80, y_padrao + 116 - i, x_padrao, y_padrao - i, false, WHITE, 1);
        }
        desenharDiagonal(tft, x_padrao + largura, y_padrao, x_padrao + 219, y_padrao +alturaTriangulo,false, WHITE,3);
        desenharDiagonal(tft, x_padrao + 46, y_padrao, x_padrao + 126, y_padrao + alturaTriangulo,true, WHITE,3);
        desenharDiagonal(tft, x_padrao + 94, y_padrao, x_padrao + 174, y_padrao + alturaTriangulo,true, WHITE,3);
        
        botaoPause3D.setCor(RED);
        botaoPause3D.desenharBotao();
        for(int k = 0; k < 3; k++){
          for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
              hashTresD[k][i][j]->ativo = false;
            }
          }
        }
        hashTresD[0][0][0]->ativo= true;
        LigaDesligaPosicao(0,0,0);
        
        for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
              setJogada(i,j,k,hash_3D[i][j][k]);
            }
          }
        }
      }


      tupla getAtivo(){
        tupla ativo;
        ativo.i = -1;
        ativo.j = -1;
        ativo.k = -1;
        for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
              if(hashTresD[i][j][k]->ativo == true){
                ativo.i = i;
                ativo.j = j;
                ativo.k = k;
                return ativo;
              }
            }
          }
        }
        return ativo; 
      }

    void LigaDesligaPosicao(int k, int i, int j){ // matriz, linha e coluna
      int color;
      bool liga = hashTresD[k][i][j]->ativo;
      if(liga)
        color = GREEN;
      else
        color = BLACK;
      Coordenada coord;
      int x,y;
      coord = hashTresD[k][i][j]->inicio;
      if(k == 0){
        for( y = coord.y; y < 36 + coord.y; y++){
          x = (280+80*y)/116;
          if(j == 1){
            x += 49;
            tft.writeFastHLine(x,y,46, color);
          }
          else if(j == 2){
            x += 98;
            tft.writeFastHLine(x,y,41, color);
          }
          else if(j == 0){
            x+=1;
            tft.writeFastHLine(x,y,45, color);
          }
        }
      }

      else if(k == 1){
        for(y = coord.y; y < 36 + coord.y; y++){
          x =(-10600+80*y)/116;
          if(j == 1){
            x += 49;
            tft.writeFastHLine(x,y,46, color);
          }
          else if(j == 0){
            x+=1;
            tft.writeFastHLine(x,y,45, color);
          }
          else if(j == 2){
            x += 98;
            tft.writeFastHLine(x,y,40, color);
          }
        }
      }
      else if(k == 2){
        for(y = coord.y; y < 36+coord.y; y++){
          x =(-21480+80*y)/116;
          if(j == 1){
            x += 49;
            tft.writeFastHLine(x,y,46, color);
          }
          else if(j == 0){
            x+=1;
            tft.writeFastHLine(x,y,45, color);
          }
          else if(j == 2){
            x += 98;
            tft.writeFastHLine(x,y,40, color);
          }
        }
      }
    }


void setSelecionado(int input){
  tupla ativo = getAtivo();
  if(input == 1){//esquerda
    if(ativo.k == 0){
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);
      //ativa o botao
      hashTresD[ativo.i][ativo.j][2] ->ativo = true;
      LigaDesligaPosicao(ativo.i, ativo.j, 2);
      setJogada(ativo.i,ativo.j,2,hash_3D[ativo.i][ativo.j][2]);
      setJogada(ativo.i,ativo.j,ativo.k, hash_3D[ativo.i][ativo.j][ativo.k]);
    }
    else if(ativo.i == -1){}
    else{
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);
      //ativa o botao
      hashTresD[ativo.i][ativo.j][ativo.k - 1] ->ativo = true;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k - 1);
      setJogada(ativo.i,ativo.j,ativo.k - 1, hash_3D[ativo.i][ativo.j][ativo.k - 1]);
      setJogada(ativo.i,ativo.j,ativo.k, hash_3D[ativo.i][ativo.j][ativo.k]);
    }
  }
  else if(input == 2){//cima
    if(ativo.j == 0 && ativo.i != 0){
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);
      //ativa o botao
      hashTresD[ativo.i - 1][2][ativo.k] ->ativo = true;
      LigaDesligaPosicao(ativo.i - 1, 2, ativo.k);
      setJogada(ativo.i - 1,2,ativo.k,hash_3D[ativo.i - 1][2][ativo.k]);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);

    }
    else if(ativo.j == 0 && ativo.i == 0){
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);

      //ligar o botao pause
      pause->setAtivo(true);
      pause->desenharBotao();
    }
    else if(ativo.i == -1){}
    else{
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);
      //ativa o botao
      hashTresD[ativo.i][ativo.j - 1][ativo.k] ->ativo = true;
      LigaDesligaPosicao(ativo.i, ativo.j - 1, ativo.k);
      setJogada(ativo.i,ativo.j - 1,ativo.k,hash_3D[ativo.i][ativo.j - 1][ativo.k]);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);      
    }
  }
  else if(input == 3){//baixo
    if(ativo.j == 2 && ativo.i != 2){
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);

      //ativa o botao
      hashTresD[ativo.i + 1][0][ativo.k] ->ativo = true;
      LigaDesligaPosicao(ativo.i + 1, 0, ativo.k);
      setJogada(ativo.i + 1,0,ativo.k,hash_3D[ativo.i + 1][0][ativo.k]);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);
    }
    else if(ativo.i == -1){
      //ligar o botao pause
      pause->setAtivo(false);
      pause->desenharBotao();

      hashTresD[0][0][0] ->ativo = true;
      LigaDesligaPosicao(0,0,0);
      setJogada(0,0,0,hash_3D[0][0][0]);

    }
    else if(ativo.j == 2 && ativo.i == 2){
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);

      //ativa o botao
      hashTresD[0][0][ativo.k] ->ativo = true;
      LigaDesligaPosicao(0, 0, ativo.k);
      setJogada(0,0,ativo.k,hash_3D[0][0][ativo.k]);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);


    }
    else{
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);

      //ativa o botao
      hashTresD[ativo.i][ativo.j + 1][ativo.k] ->ativo = true;
      LigaDesligaPosicao(ativo.i, ativo.j + 1, ativo.k);
      setJogada(ativo.i,ativo.j + 1,ativo.k,hash_3D[ativo.i][ativo.j + 1][ativo.k]);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);
    }
  }
  else if(input == 4){//direita
    if(ativo.k == 2){
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);
      //ativa o botao
      hashTresD[ativo.i][ativo.j][0] ->ativo = true;
      LigaDesligaPosicao(ativo.i, ativo.j, 0);
      setJogada(ativo.i,ativo.j,0,hash_3D[ativo.i][ativo.j][0]);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);        
    }
    else if(ativo.i == -1){}
    else{
      //desliga o botao ativo
      hashTresD[ativo.i][ativo.j][ativo.k] ->ativo = false;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k);
      //ativa o botao
      hashTresD[ativo.i][ativo.j][ativo.k + 1] ->ativo = true;
      LigaDesligaPosicao(ativo.i, ativo.j, ativo.k + 1);
      setJogada(ativo.i,ativo.j,ativo.k + 1,hash_3D[ativo.i][ativo.j][ativo.k + 1]);
      setJogada(ativo.i,ativo.j,ativo.k,hash_3D[ativo.i][ativo.j][ativo.k]);
    }
  }
  delay(250);
}

  void setJogada(int k, int i, int j, int turno){
        hashTresD[k][i][j]->type = turno;
        int x = 0;
        int y = 0;
        int y_superior = 69;
        int x_superior = 50;
        if(k == 0){
          switch(i){
            case 0:
              y = int(y_superior + 116/6);
              break;
            case 1:
              y = int(y_superior + 116/2);
              break;
            case 2: 
              y = int(y_superior + 5*(116/6));
              break;
          }
          switch(j){
            case 0:
              x = (140/6 +(280+80*y)/116);
              break;
            case 1:
              x = (140/2 +(280+80*y)/116);
              break;
            case 2:
              x = (5*(140/6) +(280+80*y)/116);
              break;
          }
        }
        else if(k == 1){
          y_superior += 116+20;
          switch(i){
            case 0:
              y = int(y_superior + 116/6);
              break;
            case 1:
              y = int(y_superior + 116/2);
              break;
            case 2: 
              y = int(y_superior + 5*(116/6));
              break;
          }
          switch(j){
            case 0:
              x = (140/6 +(-10600+80*y)/116);
              break;
            case 1:
              x = (140/2 +(-10600+80*y)/116);
              break;
            case 2:
              x = (5*(140/6) +(-10600+80*y)/116);
              break;
          }

        }
        else if(k == 2){
          y_superior += 2*(116+20);
          switch(i){
            case 0:
              y = int(y_superior + 116/6);
              break;
            case 1:
              y = int(y_superior + 116/2);
              break;
            case 2: 
              y = int(y_superior + 5*(116/6));
              break;
          }
          switch(j){
            case 0:
              x = (140/6 +(-21480+80*y)/116);
              break;
            case 1:
              x = (140/2 +(-21480+80*y)/116);
              break;
            case 2:
              x = (5*(140/6) +(-21480+80*y)/116);
              break;
          }
        }
        if (turno == 1)
          desenhaElipse(&tft, x+2, y+2, 14, 10, 45, BLUE,3);
        else if(turno == 2)
          desenhaElipse(&tft, x+2, y+2, 14, 10, 45, RED, 3);
      }
      
      void zeraVariaveis(){
        for(int k = 0; k < 3; k++){
          for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
              hashTresD[k][i][j]->type = 0;
              hashTresD[k][i][j]->ativo = false;
            }
          }
        }
        hashTresD[0][0][0]->ativo= true;     
      }
      tupla getCoords(){
        tupla coord;
        if(pause->ativo()){
          coord.i = -1;
          coord.j = -1;
          coord.k = -1;
        }
        else{
          for(int i = 0; i <3 ; i++){
            for(int j = 0; j < 3; j++){
              for(int k = 0; k < 3; k++){
                if(hashTresD[i][j][k]->ativo){
                  coord.k = i;
                  coord.i = j;
                  coord.j = k;
                }
              }
            }
          }
        }
        return coord;   
      }
};       


#endif