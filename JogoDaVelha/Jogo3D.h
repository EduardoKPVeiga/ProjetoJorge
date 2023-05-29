#ifndef _JOGO_3D_
#define _JOGO_3D_
#include "stdafx.h"
#include"Botao.h"
class Jogo3D{
    private:
      int ativo;
      Botao* pause;
    public:
      int vetorPossibilidades[28];
      quadradoHash3D hashTresD[3][3][3];
      Jogo3D(){
        pause = NULL;
        quadradoHash3D = q;
        for(int i = 0; i < 3 ; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                   hashTresD[i][j][k].ativo = false;
                }
            }
        }
      }
      ~Jogo3D(){
        pause = NULL;
      }
      void criaObjetos(){

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
        delay(200);
}
};
#endif