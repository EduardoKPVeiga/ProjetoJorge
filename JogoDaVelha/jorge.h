#pragma once

#include <stdio.h>
#include <stdlib.h>

//char jogador1[50], jogador2[50];
int player1 = 1;
int player2 = 2;
int jogo[3][3];

void inicializarMatriz() {
    int i,j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            jogo[i][j] = 0;
        }
    }
}

int getJogoAt(int _x, int _y){
  return jogo[_x][_y];
}

int eValido(int pos) {
    if(pos == 1 || pos == 2)
        return 1;
    else
        return 0;
}

bool coordenadaEhValida(int _x, int _y) {
    if(_x >= 0 && _x < 3) {
        if(_y >= 0 && _y < 3)
            return 1;
    }
    return 0;
}

bool posicaVazia(int x, int y) {
    if(jogo[x][y] == 0)
        return 1;
    return 0;
}

bool fazerJogada(int _i, int _j, short _jogada) {
  if(!posicaVazia(_i, _j)){
    return false;
  }
  else {
    if(_jogada > 0){
      jogo[_i][_j] = 1;
    }
    else{
      jogo[_i][_j] = 2;
    }
    return true;
  }
}

int ganhouLinhas() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[i][j]) && jogo[i][j] == jogo[i][j+1])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int ganhouColunas() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[j][i]) && jogo[j][i] == jogo[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int ganhoudiagPrincipal() {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int ganhoudiagSecundaria() {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][3-i-1]) && jogo[i][3-i-1] == jogo[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

bool jogoGanho() {
  int ganhou = 0;
  ganhou += ganhouLinhas();
  ganhou += ganhouColunas();
  ganhou += ganhoudiagPrincipal();
  ganhou += ganhoudiagSecundaria();
  if(ganhou > 0)
    return 1;  
  return 0;
}