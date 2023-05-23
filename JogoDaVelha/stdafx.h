#pragma once

//Libraries
#include <stdio.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
//CALIBRAR LCD
#define YP A3
#define XM A2
#define YM 9
#define XP 8
#define TS_LEFT 196
#define TS_RT   897
#define TS_TOP  170
#define TS_BOT  941

//ENUM
enum Estados{
	MENU_INICIAL,
	MENU_PAUSE,
  MENU_ESCOLHA_JOGADORES,
	JOGO_SINGLEPLAYER2D,
	JOGO_MULTIPLAYER2D,
  JOGO_SINGLEPLAYER3D,
  JOGO_MULTIPLAYER3D
};

int** createArray();
int*** create_matrix_array();
void desenharDiagonal(MCUFRIEND_kbv tft,int x0, int y0, int x1, int y1, bool esquerda, uint16_t color, int16_t espessura);
void desenhaElipse(MCUFRIEND_kbv *tft,int centerX, int centerY, int xRadius, int yRadius, float angle, uint16_t color, int largura);
//Variaveis globais
int cont;
int turn;
bool newGame=1;
enum Estados estadoAtual; //enum para o estado atual
MCUFRIEND_kbv tft; //tela
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
bool single = -9;
bool tresD = -9;
int** hash = createArray();
int*** hash_3D = create_matrix_array();

//Structs
typedef struct{
	int i, j, k;
}tupla;

typedef struct{
	int x, y;
}Coordenada;


//Defines
#define AI 1
#define PLAYER_2 2
#define N 3
//ON/OFF
#define LIGADO         0x07E0
#define DESLIGADO      0xF800
//Pressão
#define MINPRESSURE 10
#define MAXPRESSURE 1000
//Colors
#define WHITE          0xFFFF
#define YELLOW         0xFFE0
#define RED            0xF800
#define BLUE           0x001F
#define BLACK          0x0000
#define GREEN          0x07E0
#define ORANGE         0XFFA500

//Funções auxiliares

//Define e retorna as coordenadas x e y
Coordenada setCoord(int x, int y){
	Coordenada coord;
  	coord.x = x;
  	coord.y = y;
  	return coord;
}

//Limpa a tela
void limparTela(MCUFRIEND_kbv tft){
  	tft.fillScreen(BLACK);
}

//Faz um update das variáveis para o loop
void update(MCUFRIEND_kbv tft){
	limparTela(tft);
	tft.setCursor(30, 50);
	tft.setTextSize(2);
	tft.setTextColor(WHITE);
}

//Aguarda um toque na tela e retorna as coordenadas do toque
TSPoint waitTouch(TouchScreen ts) {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    /*getButtonsPressured(30,31,32,33) */
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE)/*|| botoes não pressionados*/);
  /*SE TROCAR PARA 320x480?*/
  p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
  
  return p;
}
/*
//Sabendo onde o usuário clicou, processa o clique
void processarClique(TSPoint p){
	//Clicou no botão iniciar com apenas 1 jogador
	if(p.x < 270 && p.x > 70 && p.y > 145 && p.y < 235){
		//Altera o estado
		estadoAtual = JOGO_SINGLEPLAYER2D;

		//Faz o botão clicado piscar
	}
	else if(p.x < 270 && p.x > 70 && p.y > 245 && p.y < 335){
		//Altera o estado
		estadoAtual = JOGO_MULTIPLAYER2D;

		//Faz o botão clicado piscar
	}
}
*/

//Desenha X ou O no local que o usuário clicar se for válido
//É preciso saber a LINHA, a COLUNA e o TURN para efetivar
void desenharJogada(int linha, int coluna, int turn, MCUFRIEND_kbv tft){
	int x, y; //variáveis auxiliares representam a coordenada x e y, respectivamente, do local onde se deve desenhar

	//Há apenas 3 casos para a coluna:
	switch(coluna){
    case 0:
      x = 53;
      break;
    case 1:
      x = 138;
      break;
    case 2:
      x = 223;
      break;
    default:
      Serial.println("Erro inesperado na funcao desenhaJogada. ERRO COLUNA");
      break;
	}

	//Agora quanto a linha
	switch(linha){
    case 0:
      y = 122;
      break;
    case 1:
      y = 207;
      break;
    case 2:
      y = 292;
      break;
    default:
      Serial.println("Erro inesperado na funcao desenhaJogada. ERRO LINHA");
      break;
	}

  delay(100);

	//Setamos o cursor na posição que queremos desenhar
	tft.setCursor(x, y);

	//Definimos o tamanho das representações
	tft.setTextSize(10, 10);

	//Variável auxiliar
	char _char;

	//Agora basta tomarmos o turn, para descobrirmos de quem é a vez e desenhar a representação pertinente
	if(turn == 1){
		tft.setTextColor(BLUE);
		_char = 'X';
	}
	else{
		tft.setTextColor(RED);
		_char = 'O';
	}

	//Por fim desenha a representação
	tft.print(_char);
}

//Não sei pra que serve
Coordenada coordenadaHash (int x, int y){
	Coordenada coord;
  coord.x = -1;
  coord.y = -1;
  if(x > 203 && x <= 288){
   	coord.x = 2;
  }
 	else if( x > 118 && x <= 203){
   	coord.x = 1;
  }
  	else if (x > 33 && x <= 118){
    	coord.x = 0;
  }

  if(y > 112 && y <= 197){
    coord.y = 0;
  }

  else if( y > 197 && y <= 282){
    coord.y = 1;
  }

  else if ( y > 282 && y <= 367){
    coord.y = 2;
  }
  
  return coord;
}

void desenhaJogadas3D(MCUFRIEND_kbv *tft,int i, int j, int k, int turno){
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
    desenhaElipse(tft,x+2,y+2,14,10,45,BLUE,3);
  else if(turno == 2)
    desenhaElipse(tft,x+2,y+2,14,10,45,RED,3);
}

//Resetar variaveis
void resetarVariaveis(){
	cont=0;
	turn=1;
}

void desenharJogoSalvo(int** hash, MCUFRIEND_kbv tft){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(hash[i][j] != 0)
        desenharJogada(i,j,hash[i][j], tft);
    }
  }
}

void desenharJogoSalvo3D(int ***hash, MCUFRIEND_kbv tft){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      for(int k = 0; k < 3; k++){
        desenhaJogadas3D(&tft,j,k,i, hash[i][j][k]);
      }
    }
  }   
}
void blanksMatrix3D(int ***arr){
    for(int k = 0; k < N ; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                arr[k][j][i] = 0;
            }
        }
    }
}
int*** create_matrix_array() {
    int*** arr = new int**[3];
    for (int i = 0; i < 3; i++) {
        arr[i] = new int*[3];
        for (int j = 0; j < 3; j++) {
            arr[i][j] = new int[3];
        }
    }
  return arr;
}

void desenharDiagonal(MCUFRIEND_kbv tft,int x0, int y0, int x1, int y1, bool esquerda, uint16_t color, int16_t espessura = 5){
  	if(esquerda){
    	for(int i = 0; i < espessura; i++){
      	tft.drawLine(x0+i, y0, x1+i  , y1, color);      
    	}
  	}
  	else{
      espessura *= -1;
      Serial.print(espessura);
    	for(int i = 0; i > espessura; i--){
      		tft.drawLine(x0 + i, y0, x1 + i , y1, color);
    	}
  	}
}
void desenhaElipse(MCUFRIEND_kbv *tft,int centerX, int centerY, int xRadius, int yRadius, float angle, uint16_t color, int largura) {
  float cosAngle = cos(angle * DEG_TO_RAD);
  float sinAngle = sin(angle * DEG_TO_RAD);
  for (int i = 0; i < largura; i++){
    xRadius +=1;
    yRadius += 1;
    for (float t = 0; t < 2 * PI; t += 0.01) {
      int x = centerX + xRadius * cos(t) * cosAngle - yRadius * sin(t) * sinAngle;
      int y = centerY + xRadius * cos(t) * sinAngle + yRadius * sin(t) * cosAngle;
      tft->drawPixel(x, y, color);
    }
  }
}

