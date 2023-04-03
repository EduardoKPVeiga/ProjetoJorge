/*
 *   CÓDIGO:  Q0684
 *   AUTOR:   BrincandoComIdeias
 *   ACOMPANHE: https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
 *   APRENDA: https://cursodearduino.net/ ; https://cursoderobotica.net
 *   COMPRE:  https://www.arducore.com.br/
 *   SKETCH:  Verificar identificador  
 *   DATA:    15/09/2021
*/

// INCLUSÃO DE BIBLIOTECAS
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

#include "jorge.h"

// DEFINIÇÕES
#define WHITE          0xFFFF
#define YELLOW         0xFFE0
#define RED            0xF800
#define BLUE           0x001F
#define BLACK          0x0000

#define LIGADO         0x07E0
#define DESLIGADO      0xF800

#define MINPRESSURE 10
#define MAXPRESSURE 1000

/*____CALIBRAR TFT LCD_____*/
#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_LEFT 196
#define TS_RT   897
#define TS_TOP  170
#define TS_BOT  941
/*______FIM DA CALIBRAÇÃO______*/

// INSTANCIANDO OBJETOS
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 É A SENSITIVIDADE

int X, Y;
long corBot[2] = {DESLIGADO, DESLIGADO};

TSPoint waitTouch() {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  
  p.x = map(p.x, TS_LEFT, TS_RT, 0, 240);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 320);
  
  return p;
}

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  
  Serial.print("Identificador do display: ");
  Serial.println(ID, HEX);
  
  tft.begin(ID);
  tft.setRotation(2);

  IntroScreen();
  inicializarMatriz();
}

void loop() {
  draw_Buttons(0);
  TSPoint p = waitTouch();
  X = p.x; Y = 330 - p.y;

  DetectButtons(); // DETECTA OS BOTOES
  delay(300);

  resetButtons();
  clearScreen();
}

void IntroScreen() {
  clearScreen();
  tft.setCursor (45, 80);
  tft.setTextSize (3);
  tft.setTextColor(WHITE);
  tft.println("JOGO DA VELHA");
  tft.setCursor (50, 110);
  tft.setTextSize (2);
  tft.setTextColor(BLUE);
  tft.println("Projeto de Oficinas");
  delay(2000);
}

void DetectButtons() {
  if (X < 200 && X > 40) {
    if (Y > 168 && Y < 240) { // LOGICA PARA O BOTAO 1
      Serial.println ("Button 1");
      if (corBot[0] == LIGADO) corBot[0] = DESLIGADO;
      else corBot[0] = LIGADO;
      draw_Buttons(1);
      //drawFrame();
    }

    if (Y > 100 && Y < 161) { // LOGICA PARA O BOTAO 2
      Serial.println ("Button 2");
      if (corBot[1] == LIGADO) corBot[1] = DESLIGADO;
      else corBot[1] = LIGADO;
      draw_Buttons(2);
      drawFrame();
    }
  }
}

void draw_Buttons(int type) {
  switch (type) {
    case 1:
      tft.fillRect  (70, 145 , 180, 90, corBot[0]);

      tft.setTextColor(BLACK);
      tft.setTextSize (2);
      tft.setCursor(105, 180);
      tft.println("1 JOGADOR");
      break;

    case 2:
      tft.fillRect  (70, 245, 180, 90, corBot[1]);

      tft.setTextColor(BLACK);
      tft.setTextSize (2);
      tft.setCursor(95, 280);
      tft.println("2 JOGADORES");
      break;

    default:
      tft.fillRect  (70, 145 , 180, 90, corBot[0]);
      tft.fillRect  (70, 245, 180, 90, corBot[1]);

      tft.setTextColor(BLACK);
      tft.setTextSize (2);

      tft.setCursor(105, 180);
      tft.println("1 JOGADOR");

      tft.setCursor(95, 280);
      tft.println("2 JOGADORES");
  }
}

void drawFrame() {
  delay(200);
  tft.fillScreen(WHITE);
  tft.setTextColor(BLACK);
  // Vertical
  tft.fillRect(100, 80, 5, 300, BLACK);
  tft.fillRect(220, 80, 5, 300, BLACK);

  // Horizontal
  tft.fillRect(20, 170, 280, 5, BLACK);
  tft.fillRect(20, 270, 280, 5, BLACK);
  
  short move = -1, move_aux = move;

  int end = 0, cont = 0;  
  while(end == 0) {
    move_aux = makeMove(move_aux);
    int i,j;
    /*
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            Serial.print("[");
            Serial.print(i);
            Serial.print("][");
            Serial.print(j);
            Serial.print("]: ");
            Serial.println(getJogoAt(i, j));
        }
    }*/
    if(move_aux != move) {
      cont++;
      move = move_aux;
      if(jogoGanho() || cont == 9)
        end = 1;
    }
  }
  
  if(cont == 9) {
    clearScreen();
    tft.setCursor (45, 80);
    tft.setTextSize (3);
    tft.setTextColor(WHITE);
    tft.println("EMPATE!");
    
    tft.setTextSize (2);    
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        tft.setCursor (45 + (i * 10), 120 + (j * 10));
      }        
    }
  }
  else {
    if(move > 0) {
      clearScreen();
      tft.setCursor (45, 80);
      tft.setTextSize (3);
      tft.setTextColor(WHITE);
      tft.println("JOGADOR 1 VENCEU!");
    } else {
      clearScreen();
      tft.setCursor (45, 80);
      tft.setTextSize (3);
      tft.setTextColor(WHITE);
      tft.println("JOGADOR 2 VENCEU!");
    }
  }
  inicializarMatriz();  
  delay(2000);
}

int makeMove(short _move) {
  TSPoint p = waitTouch();

  Serial.print("Touch.y: ");
  Serial.println(p.y);

  Serial.print("Touch.x: ");
  Serial.println(p.x);

  if(p.x > 170 && p.x <= 240) {
    _move = moveY(50, p.y, _move, 0);
  }
  else if(p.x > 70 && p.x <= 170) {
    _move = moveY(150, p.y, _move, 1);
  }
  else {
    _move = moveY(250, p.y, _move, 2);
  }
  //Serial.print("MakeMove: ");
  //Serial.println(_move);  
  return _move;
}

int moveY(int _x, int _y, short _move, int _xindex) {
  if(_y > 0 && _y <= 100) {
    //if(fazerJogada(_xindex, 0, _move))
      _move = drawMove(_x, 120, _move);
  }
  else if(_y > 100 && _y <= 180) {
    //if(fazerJogada(_xindex, 1, _move))
      _move = drawMove(_x, 210, _move);
  }
  else {
    //if(fazerJogada(_xindex, 2, _move))
      _move = drawMove(_x, 300, _move);
  }
  //Serial.print("MoveY: ");
  //Serial.println(_move);
  return _move;
}

int drawMove(int _x, int _y, short _move) {
  delay(200);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.setCursor(_x, _y);
  char moveChar = "";
  if(_move > 0) {  
    moveChar = 'X';
  }
  else { 
    moveChar = '0';
  }
  
  if(fazerJogada(indiceX(_x), indiceY(_y), _move)){
    _move = _move * (-1);
    tft.print(moveChar);
  }
  return _move;
}

int indiceY(int _y){
  if(_y == 120) {
    return 0;
  }
  else if(_y == 210) {
    return 1;
  }
  else {
    return 2;
  }
}

int indiceX(int _x){
  if(_x == 50) {
    return 0;
  }
  else if(_x == 150) {
    return 1;
  }
  else {
    return 2;
  }
}

void clearScreen() {
  tft.fillScreen(BLACK);
}

void resetButtons() {
  corBot[0] = DESLIGADO;
  corBot[1] = DESLIGADO;
}
