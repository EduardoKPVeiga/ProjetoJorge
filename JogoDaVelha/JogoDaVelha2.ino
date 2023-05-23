//
#include "GerenciadorDeEstados.h"
#include "IntroducaoJogo.h"

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

void loop(){/*
	update(tft);
	GerenciarEstados();*/
   // put your main code here, to run repeatedly:
  int aux = analogRead(A15);
  botao(aux);
  delay(100);

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

void plotX(MCUFRIEND_kbv *tft, int x, int y, int size, int angle, uint16_t color) {
  
  int xEnd = 0;
  int yEnd = 0;
  float cosAngle = cos(angle * DEG_TO_RAD);
  float sinAngle = sin(angle * DEG_TO_RAD);
  
  xEnd = x + 8;
  yEnd = y + 12;
  DrawAngledLine(tft, x, y, xEnd, yEnd, 5, color);

  xEnd = x - 8;
  yEnd = y - 12;
  DrawAngledLine(tft, x, y, xEnd, yEnd, 5, color);





}

void DrawAngledLine(MCUFRIEND_kbv *tft ,int x, int y, int x1, int y1, int size, int color){
  float dx = (size/2.0)*(x - x1)/sqrt(sq(x-x1)+sq(y-y1));
  float dy = (size/2.0)*(y - y1)/sqrt(sq(x-x1)+sq(y-y1));
  tft->fillTriangle(x + dx,y - dy, x - dx, y + dy , x1 + dx, y1 - dy,color);
  tft->fillTriangle(x - dx, y + dy, x1 - dx, y1 + dy, x1 + dx, y1 - dy, color);
}














