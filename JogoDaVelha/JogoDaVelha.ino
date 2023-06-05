//
#include "GerenciadorDeEstados.h"
#include "IntroducaoJogo.h"
#include "Jogo2D.h"
#include "LogicaJogo.h"
#include "stdafx.h"

int ***qqcoisa = create_matrix_array();
Coordenada hashTresD[3][3][3];

void setup(){
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  
  Serial.print("Identificador do display: ");
  Serial.println(ID, HEX);
  
  //Inicializando a variável tft
  tft.begin(ID);
  tft.setRotation(2);

  //Inicializando o hash com zeros
  matrizEmBranco(hash);

  //Inicializando o estadoAtual
  estadoAtual = MENU_INICIAL;

  //Inicializando o turn
  turn = 0;

  //Inicializando cont
  cont = 0;
  
  //Desenhando a INTRODUÇÃO
  limparTela(tft);
  introducao(tft);

  //É o tempo que a introdução vai ficar na tela
  
}

void loop(){
	update(tft);
	GerenciarEstados();
}
