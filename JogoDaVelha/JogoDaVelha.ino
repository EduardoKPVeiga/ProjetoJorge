//
#include "GerenciadorDeEstados.h"
#include "IntroducaoJogo.h"
#include "Jogo2D.h"
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
  delay(1000);
  limparTela(tft);

}

void loop(){
	update(tft);
	GerenciarEstados();
}

void botao(int input){
  if(input >=0 && input <= 10){
    limparTela(tft);
    tft.fillCircle(160, 240, 33, GREEN);
  	tft.fillCircle(160, 240, 28, BLACK);
  }
  else if(input >=132  && input <= 152){
    limparTela(tft);
    tft.fillCircle(160, 240, 33, RED);
  	tft.fillCircle(160, 240, 28, BLACK);
  }
  else if(input >= 292 && input <= 312){
    limparTela(tft);
    tft.fillCircle(160, 240, 33, BLUE);
  	tft.fillCircle(160, 240, 28, BLACK);
  }
  else if(input >=480 && input <= 500){
    limparTela(tft);
    tft.fillCircle(160, 240, 33, WHITE);
  	tft.fillCircle(160, 240, 28, BLACK);
  }
  else if(input >= 727 && input <= 747){
    limparTela(tft);
    tft.fillCircle(160, 240, 33, YELLOW);
  	tft.fillCircle(160, 240, 28, BLACK);
  }
}
