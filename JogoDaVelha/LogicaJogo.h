/*
* 
*/

#pragma once
#include "stdafx.h"
#include "Botao.h"
//Assinaturas das funções
tupla minimax_alphabeta(int **hash, bool isMaximizing, int depth, int alpha, int beta);
tupla bestPlay(int **hash);
int **createArray();
void matrizEmBranco(int **arr);
void printArray(int **arr);
int check_winner(int **arr);
int check_winner_3D(int ***arr);
bool valid_play(int **arr, int i, int j);
bool valid_play3D(int ***arr, int i, int j, int k);
tupla bestPlay3D(int ***hash);
tupla minimax3D (int ***hash, bool isMaximaxing, int depth,  int alpha, int beta);

/*botoes de pausa*/
Coordenada tamanhoBotao = setCoord(90,45);
Coordenada posicaoBotao = setCoord(205,25);
Coordenada posicaoCursor = setCoord(220,40);
Botao botaoPause3D(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, RED,"PAUSE");
Botao botaoPause(posicaoBotao, tamanhoBotao, posicaoCursor, &tft, RED,"PAUSE");
tupla minimax_alphabeta(int **hash, bool isMaximizing, int depth, int alpha, int beta){
    int result = check_winner(hash);
    if (result != -1){
        tupla tup;
        tup.j = depth;
        switch (result){
            case 0:
                tup.i = 0;
                return tup;
            case 1:
                tup.i = 10;
                return tup;
            case 2:
                tup.i = -10;
                return tup;
        }
    }
    tupla bestScore;
    tupla score;
    if (isMaximizing){
        bestScore.i = INT16_MIN;
        bestScore.j = INT16_MAX;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if (hash[i][j] == 0){
                    hash[i][j] = AI;
                    score = minimax_alphabeta(hash, false, depth + 1, alpha, beta);
                    hash[i][j] = 0;
                    if (score.i > bestScore.i || (score.i == bestScore.i && score.j < bestScore.j)){
                        bestScore.i = score.i;
                        bestScore.j = score.j;
                    }
                    alpha = max(alpha, bestScore.i);
                    if (beta <= alpha){
                        break;
                    }
                }
            }
        }
        return bestScore;
    }
    else{
        bestScore.i = INT16_MAX;
        bestScore.j = INT16_MAX;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if (hash[i][j] == 0){
                    hash[i][j] = PLAYER_2;
                    score = minimax_alphabeta(hash, true, depth + 1, alpha, beta);
                    hash[i][j] = 0;
                    if (score.i < bestScore.i || (score.i == bestScore.i && score.j < bestScore.j)){
                        bestScore.i = score.i;
                        bestScore.j = score.j;
                    }
                    beta = min(beta, bestScore.i);
                    if (beta <= alpha){
                        break;
                    }
                }
            }
        }
        return bestScore;
    }
}

tupla bestPlay(int **hash){
    int bestScore = INT16_MIN;
    int depth = INT16_MAX;
    tupla move;
    move.i = 0;
    move.j = 0;
    tupla score;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (hash[i][j] == 0){
                hash[i][j] = AI;
                score = minimax_alphabeta(hash, false, 0, INT16_MIN, INT16_MAX);
                hash[i][j] = 0;
                if (bestScore < score.i || (bestScore == score.i && score.j < depth)){
                    bestScore = score.i;
                    depth = score.j;
                    move.i = i;
                    move.j = j;
                }
            }
        }
    }
    return move;
}

tupla bestPlay3D(int ***hash){
    int bestScore = INT16_MIN;
    int profundidade = INT16_MAX;
    tupla movimento;
    movimento.i = 0;
    movimento.j = 0;
    movimento.k = 0;
    tupla score; 
    for (int k = 0; k < N; k++){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if(hash[k][i][j] == 0){
                    hash[k][i][j] = AI;
                    score = minimax3D(hash,false,0, INT16_MIN, INT16_MAX);
                    hash[k][i][j] = 0;
                    if (((bestScore == 0)&&(score.i < 0))||(bestScore < score.i) || (bestScore  == score.i && score.j > profundidade)){
                        bestScore = score.i;
                        profundidade = score.j;
                        movimento.i = i;
                        movimento.j = j;
                        movimento.k = k;
                    }
                }
            }
        }
    }
    return movimento;
}
tupla minimax3D (int ***hash, bool isMaximaxing, int depth,  int alpha, int beta){
  int result = check_winner_3D(hash);
  if (result != -1){
    tupla tup;
    tup.j = depth;
    switch (result ){
    case 0:
      tup.i = 0;
      return tup;
    case 1:
      tup.i = 3 + 1 - depth;;
      return tup;
    case 2:
      tup.i = depth - 3- 1;
      return tup;
    }
  }
  if(depth >= 3){
    tupla tup;
    tup.i = 0;
    tup.j = depth;
    return tup;
  }
    
    
tupla bestScore;
tupla score;
if(depth < 3){
    if(isMaximaxing){
        bestScore.i = INT16_MIN;
        bestScore.j = INT16_MAX; 
        for(int k = 0; k < N; k++){
            for(int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    if(hash[k][i][j] == 0){
                        hash[k][i][j] = AI;
                        //chama a recursão
                        score = minimax3D(hash, false, depth + 1, alpha, beta);
                        hash[k][i][j] = 0;
                        if((score.i > bestScore.i) || (score.i == bestScore.i && score.j < bestScore.j)){
                            bestScore.i = score.i;
                            bestScore.j = score.j;
                        }
                        alpha = max(alpha, bestScore.i);
                        if(beta <= alpha)
                          return bestScore;
                    }
                }
            }
        }
    } else{ // MINIMAZING
        bestScore.i = INT16_MAX;
        bestScore.j = INT16_MIN; 
        for(int k = 0; k < N; k++){
            for(int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    if(hash[k][i][j] == 0){
                        hash[k][i][j] = PLAYER_2;
                        //chama a recursão
                        score = minimax3D(hash,true, depth + 1, alpha, beta);
                        hash[k][i][j] = 0;

                        if((score.i < bestScore.i) || (score.i == bestScore.i && score.j > bestScore.j)){
                            bestScore.i = score.i;
                            bestScore.j = score.j;
                        }
                        beta = min(beta, bestScore.i);
                        if (beta <= alpha){
                            return bestScore;
                        }
                    }
                }
            }
        }
      
    }     
  }
}

//Cria uma matriz inicializada com 0
void matrizEmBranco(int **arr){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arr[j][i] = 0;
        }
    }
}
void matrizEmBranco3D(int ***arr){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < 3; k++){
              arr[i][j][k] = 0;
            }
        }
    }
}

int **createArray(){
    int **arr = new int*[N];
    for (int i = 0 ; i < N ; i++){
        arr[i] = new int[N];
    }
    matrizEmBranco(arr);
    return arr;
}

int check_winner(int **arr){
    int i,j;
    for( i = 0; i < 3; i++){
        if(arr[i][0] == arr[i][1] && arr[i][1] == arr [i][2] && arr[i][2] != 0)
            return arr[i][0];
        if(arr[0][i] == arr[1][i] && arr[1][i] == arr [2][i] && arr[2][i] != 0)
            return arr[0][i];
    }

    if(arr [1][1] != 0){
        if(arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
            return arr[0][0];
        if (arr[0][2] == arr[2][0] && arr [0][2] == arr[1][1])
            return arr[0][2];
    }
    int cont = 0;
    for( i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            if(arr[i][j] != 0)
                cont++;
    }

    if(cont == 9)
        return 0;
    return -1;
}

int check_winner_3D(int ***arr){
    int i,j,k;
    /*Casos de ganhar em uma das matrizes*/
    for (k = 0; k < 3; k++){
        for( i = 0; i < 3; i++){
        if(arr[k][i][0] == arr[k][i][1] && arr[k][i][1] == arr [k][i][2] && (arr[k][i][2] != 0))
          return arr[k][i][0];
        if(arr[k][0][i] == arr[k][1][i] && arr[k][1][i] == arr[k][2][i] && (arr[k][2][i] != 0))
          return arr[k][0][i];
        }
        if(arr [k][1][1] != 0){
          if(arr[k][0][0] == arr[k][1][1] && arr[k][1][1] == arr[k][2][2])
            return arr[k][0][0];
          if (arr[k][0][2] == arr[k][2][0] && arr[k][0][2] == arr[k][1][1])
            return arr[k][0][2];  
      }
    }
     /*Casos de ganhar em mais de uma matriz*/
    for(k = 0; k < 3; k++){
        //coluna 3D
        if((arr[0][0][k] == arr[1][1][k]) && arr[1][1][k] == arr[2][2][k] && (arr[2][2][k] != 0))
            return arr[0][0][k];
        if((arr[0][2][k] == arr[1][1][k])  && (arr[1][1][k] == arr[2][0][k] )&& (arr[2][0][k] != 0))
            return arr[0][2][k];
        //linhas 3D
        if((arr[0][k][0] == arr[1][k][1]) && (arr[1][k][1] == arr[2][k][2]) && (arr[2][k][2] != 0))
            return arr[0][k][0];
        if((arr[0][k][2] == arr[1][k][1]) && (arr[1][k][1] == arr[2][k][0]) && (arr[2][k][0] != 0))
            return arr[0][k][2];

    }
    //Diagonal 3D
    if(arr[1][1][1] != 0){
        if(arr[0][0][0] == arr [1][1][1] && arr [1][1][1]  == arr[2][2][2])
            return arr[0][0][0];
        if(arr[0][0][2] == arr[1][1][1] && arr [1][1][1] == arr[2][2][0])
            return arr[0][0][2];
        if(arr[0][2][0] == arr[1][1][1] && arr [1][1][1] == arr[2][0][2])
            return arr[1][1][1];
        if(arr[0][2][2] == arr[1][1][1] && arr [1][1][1] == arr[2][0][0])
            return arr[1][1][1];
    }
    int cont = 0;
    for(k = 0; k < 3; k++){
        for( i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(arr[k][i][j] != 0)
                    cont++;
            }
        }
    }
    if(cont == 27)
        return 0;
    return  -1;
}
bool valid_play3D(int ***arr, int i, int j, int k){
  if(i == -1 || j == -1 || k == -1){
    return false;
  }
  return arr[k][i][j] == 0 ? true : false;
}

bool valid_play(int **arr, int i, int j){
  if(i == -1 || j == -1){
    return false;
  }
  return (arr[i][j] == 0 ? true : false);
}

tupla transformaTouch(int x, int y){
  tupla coord;
  coord.i = -1;
  coord.j = -1;
  coord.k = -1;
  int xAux;
  if(y >= 69 && y <= 185){
    coord.k = 0;
    xAux =(280+80*y)/116;
    if(x >= xAux && x < (xAux + 140)){
      if(x >= xAux && x < (xAux + 46)){
        coord.j = 0;
      }
      else if(x >= (xAux + 46) && x < (xAux + 96)){
        coord.j = 1;
      }
      else if(x >= (xAux + 96) && x <= (xAux + 140)){
        coord.j = 2;
      }
    }
    if(y>=69 && y<= 108){
      coord.i = 0;
    }//39 e 77
    else if(y >= 111 && y <= 150){
      coord.i = 1;
    }
    else if(y >= 153 && y <= 185){
      coord.i = 2;
    }
  }
  else if(y>=205 && y <= 321){
    coord.k = 1;
    xAux =(-10600+80*y)/116;
    if(x >= xAux && x < (xAux + 140)){
      if(x >= xAux && x < (xAux + 46)){
        coord.j = 0;
      }
      else if(x >= (xAux + 46) && x < (xAux + 96)){
        coord.j = 1;
      }
      else if(x >= (xAux + 96) && x <= (xAux + 140)){
        coord.j = 2;
      }
    }
    if(y >= 205 && y <= 244){
      coord.i = 0;
    }//39 e 77
    else if(y >= 247 && y <= 283){
      coord.i = 1;
    }
    else if(y >= 286 && y <= 321){
      coord.i = 2;
    }
  }
  else if(y >= 341 && y <= 457){
    coord.k = 2;
    xAux =(-21480+80*y)/116;
    if(x >= xAux && x < (xAux + 140)){
      if(x >= xAux && x < (xAux + 46)){
        coord.j = 0;
      }
      else if(x >= (xAux + 46) && x < (xAux + 96)){
        coord.j = 1;
      }
      else if(x >= (xAux + 96) && x <= (xAux + 140)){
        coord.j = 2;
      }
    }
    if(y >= 341 && y <= 380){
      coord.i = 0;
    }//39 e 77
    else if(y >= 383 && y <= 409){
      coord.i = 1;
    }
    else if(y >= 412 && y <= 457){
      coord.i = 2;
    }
  }
  return coord;
}


//Desenhos dos jogos
//Desenha o jogo da velha
void desenharJogoDaVelha(MCUFRIEND_kbv tft){
  	delay(200);
  	tft.fillScreen(WHITE);
  	tft.setTextColor(BLACK);
  	//Vertical
  	tft.fillRect(295, 90, 5, 270, BLACK);
  	tft.fillRect(205, 90, 5, 270, BLACK);
  	tft.fillRect(115, 90, 5, 270, BLACK);
  	tft.fillRect( 25, 90, 5, 270, BLACK);

  	// Horizontal
  	tft.fillRect(25, 90, 270, 5, BLACK);
  	tft.fillRect(25, 180, 270, 5, BLACK);
  	tft.fillRect(25, 270, 270, 5, BLACK);
  	tft.fillRect(25, 360, 270, 5, BLACK);

    botaoPause.setCor(RED);
    botaoPause.desenharBotao();
  	delay(200);
    /*tft.fillRect(205, 25, 90, 45, RED);
  	tft.setCursor(220, 40);
  	tft.setTextSize(2);
  	tft.setTextColor(BLACK);
  	tft.print("PAUSE");*/
}


void desenharJogoDaVelha3D(MCUFRIEND_kbv tft){
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
  delay(200);
}