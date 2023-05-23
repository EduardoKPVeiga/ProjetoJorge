/*
* É a animação inicial, simplesmente desenha um jogo da velha e algumas jogadas
*/
#include "stdafx.h"

void introducao(MCUFRIEND_kbv tft){
  	tft.setCursor (45, 80);
  	tft.setTextSize (3);                        //Escreve JOGO DA VELHA na tela
  	tft.setTextColor(WHITE);
  	tft.println("Jogo da velha");

  	tft.setCursor (50, 110);
  	tft.setTextSize (2);                        //Escreve PROJETO DE OFICINAS na tela
  	tft.setTextColor(BLUE);
  	tft.println("Projeto de Oficinas");
  	delay(100);

	//Vertical
  	delay(400);
  	tft.fillRect(115, 160, 5, 270, WHITE);
  	delay(400);
  	tft.fillRect(205, 160, 5, 270, WHITE);
  	delay(400);

  	//Horizontal
  	tft.fillRect(25, 240, 270, 5, WHITE);
 	  delay(100);
  	tft.fillRect(25, 330, 270, 5, WHITE);
  	delay(100);

  	//jogadas
  	tft.fillCircle(70, 200, 33, RED);
  	tft.fillCircle(70, 200, 28, BLACK);
  	delay(400);

  	tft.setTextSize(8,8);
  	tft.setTextColor(BLUE);
  	tft.setCursor(55, 260);
  	tft.print('X');
  	delay(400);

  	tft.fillCircle(160, 290, 33, RED);
  	tft.fillCircle(160, 290, 28, BLACK);
  	delay(400);
  
  	tft.setTextSize(8,8);
  	tft.setTextColor(BLUE);
  	tft.setCursor(235, 350);
  	tft.print('X');
  	delay(400);

  	tft.fillCircle(250, 200, 33, RED);
  	tft.fillCircle(250, 200, 28, BLACK);
  	delay(400);

  	tft.setTextSize(8,8); 
  	tft.setTextColor(BLUE); 
  	tft.setCursor(145, 170);
  	tft.print('X');
  	delay(400);

  	tft.fillCircle(70, 380, 33, RED);
  	tft.fillCircle(70, 380, 28, BLACK);
  	delay(400);
  
  	desenharDiagonal(tft, 290, 160, 20, 430,true, WHITE,5);
}
