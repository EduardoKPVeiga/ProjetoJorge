/*
* Um gerenciador de estados primitivo
*/
#pragma once
#include "LogicaJogo.h"
#include "MenuPause.h"
#include "MenuInicial.h"
#include "MenuEscolhaJogadores.h"
#include "Botao.h"

void GerenciarEstados(){
/*=====================================================================================================*/
//MENU INICIAL
	if(estadoAtual == MENU_INICIAL){
		//Desenha o menu inicial
		MenuInicial _menuInicial(BLACK, &tft, true, "ESCOLHA O MODO DE JOGO");
		_menuInicial.desenharMenu();

		//Recebe input do usuário, aguarda o click
		TSPoint p = waitTouch(ts);

		//Agora é preciso processar esse ponto clicado
		//processarClique(p, &estadoAtual);
  	//Clicou no botão iniciar com apenas 1 jogador
	  if(p.x < 270 && p.x > 70 && p.y > 120 && p.y < 210){
		  //Altera o estado
		  estadoAtual = MENU_ESCOLHA_JOGADORES;
		  tresD = 0;
		  newGame = 1;
		  //Faz o botão clicado trocar de cor
      _menuInicial.ligaBotao(0);
      
	  }
	  else if(p.x < 270 && p.x > 70 && p.y > 240 && p.y < 330){
		  //Altera o estado
		  estadoAtual = MENU_ESCOLHA_JOGADORES;
		  tresD = 1;
		  newGame = 1;
		  //Faz o botão clicado piscar
      _menuInicial.ligaBotao(1);
	  }
    delay(100); 
  }
/*=====================================================================================================*/
  else if(estadoAtual == MENU_ESCOLHA_JOGADORES){
    //Desenha o menu inicial
		MenuEscolhaJogadores _menuEscolhaJogadores(BLACK, &tft, true, "ESCOLHA N° DE JOGADORES");
		_menuEscolhaJogadores.desenharMenu();

		//Recebe input do usuário, aguarda o click
		TSPoint p = waitTouch(ts);

		//Agora é preciso processar esse ponto clicado
		//processarClique(p, &estadoAtual);
  	//Clicou no botão iniciar com apenas 1 jogador
    if(p.x < 270 && p.x > 70){
	    if( p.y > 100 && p.y < 190){
        //Altera o estado
        single = 1;
        if(tresD)
          estadoAtual = JOGO_SINGLEPLAYER3D;
        else
          estadoAtual = JOGO_SINGLEPLAYER2D;
        _menuEscolhaJogadores.ligaBotao(0);
      //Faz o botão clicado trocar de cor
	    }
	    else if(p.y > 220 && p.y < 310){
        single = 0;
        if(tresD)
          estadoAtual = JOGO_MULTIPLAYER3D;
        else
          estadoAtual = JOGO_MULTIPLAYER2D;
        _menuEscolhaJogadores.ligaBotao(1);
	    } 
      else if(p.y >340 && p.y < 430){
        estadoAtual = MENU_INICIAL;
        _menuEscolhaJogadores.ligaBotao(2);
        delay(100);
      }
    }
  }

/*=====================================================================================================*/
  //JOGO SINGLEPLAYER2D
	else if(estadoAtual == JOGO_SINGLEPLAYER2D){
    	Serial.println("Case 2");
		int linha, coluna,flagBotaoPausa=0; //variaveis auxiliares
		if(newGame){
      		//resetar as variáveis
			resetarVariaveis();
			matrizEmBranco(hash);

      srand(time(NULL));

			desenharJogoDaVelha(tft);
			//Aqui é o caso SINGLEPLAYER, então é preciso definir onde a MÁQUINA vai jogar
			//Vamos assumir que sempre será um novo jogo, nós definimos que a máquina sempre joga primeiro
			turn = 1;
			coluna = rand()%3;
			linha = rand()%3;
			hash[linha][coluna] = AI;
			desenharJogada(linha, coluna, turn, tft);
			turn = 2;
			cont++;
		}
    //Caso não seja um novo jogo
		else{
			desenharJogoDaVelha(tft);
			desenharJogoSalvo(hash, tft);
		}

		
		while(check_winner(hash) == -1 && cont < 9){
			//Se for a vez da máquina
			if(turn == 1){
				tupla aiPlay = bestPlay(hash);
				linha = aiPlay.i;
				coluna = aiPlay.j;
				hash[linha][coluna] = AI;
				//delay(250);
				desenharJogada(linha, coluna, turn, tft);
				turn = 2;
				cont++; 				
			}
			//Se for a vez do player
			else{
				TSPoint p = waitTouch(ts);
				//Checar botão de pausa
				if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
					flagBotaoPausa=1;
					break;
				}

				Coordenada coord = coordenadaHash(p.x, p.y);
				linha = coord.y;
				coluna = coord.x;
				//É preciso saber se a posição clicada é válida
				if(valid_play(hash, linha, coluna)){
					hash[linha][coluna] = 2;
					desenharJogada(linha, coluna, turn, tft);
					turn=1;
					cont++;
				}
				else
					Serial.println("Invalid play");
			}
		}
			//Imprimir uma mensagem sobre quem venceu
		if(check_winner(hash) != -1){
			if(single){
				limparTela(tft);
				tft.setCursor (45, 80);
				tft.setTextSize (2);
				tft.setTextColor(WHITE);
				switch (check_winner(hash))
				{
				case 0:
					tft.println("EMPATE!");
					break;
				case 1:
					tft.println("AI VENCEU! :) :) ");
					break;
				case 2:
					tft.println("JOGADOR VENCEU ! ;( ;( ");
				}
			}
		}
	  delay(100);
		
		if(flagBotaoPausa){
			estadoAtual = MENU_PAUSE;
      botaoPause.setCor(GREEN);
      botaoPause.desenharBotao();
		}
		else{
			estadoAtual = MENU_INICIAL;
			//Como saiu do loop então o jogo acabou e deve zerar o cont, o turn e o hash, caso contrário ele sairá automaticamente do loop
			resetarVariaveis();
			matrizEmBranco(hash);
		}
	}
/*=====================================================================================================*/
  //JOGO MULTIPLAYER2D
  else if(estadoAtual == JOGO_MULTIPLAYER2D){
  	


    //Variaveis auxiliares
    int linha, coluna, flagBotaoPausa=0;

  	if(newGame){
  		resetarVariaveis();
  		matrizEmBranco(hash);
		desenharJogoDaVelha(tft);
  	}

  	else{
  		desenharJogoDaVelha(tft);
  		desenharJogoSalvo(hash, tft);
  	}

  	while(check_winner(hash) == -1 && cont < 9){
  		//Assumindo sempre um novo jogo
  		//Receber a entrada 
  		TSPoint p = waitTouch(ts);

  		//Processar a entrada, checar se é menu de pause
  		if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
  			//Alterar o estado
  			//estadoAtual = MENU_PAUSE;
  			flagBotaoPausa = 1;
  			break;
  		}

  		Coordenada coord = coordenadaHash(p.x, p.y);
  		linha = coord.y;
  		coluna = coord.x;

  		//Analisa se o ponto é válido e desenha caso for
  		if(turn == 1){
  			if(valid_play(hash, linha, coluna)){
  				hash[linha][coluna] = 1;
  				desenharJogada(linha, coluna, turn, tft);
  				turn = 2;
  				cont++;
  			}
  			else
  				Serial.println("Invalid play!");
  		}
  		else{
  			if(valid_play(hash, linha, coluna)){
  				hash[linha][coluna] = 2;
  				desenharJogada(linha, coluna, turn, tft);
          		turn=1;
  				cont++;
  			}
  		}  		
  	}

  	//Alterando o estado
		if(flagBotaoPausa == 0){
			estadoAtual = MENU_INICIAL;
      limparTela(tft);  
      tft.setCursor (45, 80);
      tft.setTextSize (2);
      tft.setTextColor(WHITE);
      switch (check_winner(hash))
      {
      case 0:
        tft.println("EMPATE!");
        break;
      case 1:
        tft.println("JOGADOR 2 VENCEU!");
        break;
      case 2:
        tft.println("JOGADOR 1 VENCEU!");
      }
			resetarVariaveis();
			matrizEmBranco(hash);
          
		}	
		else{
			estadoAtual = MENU_PAUSE;
      botaoPause.setCor(GREEN);
      botaoPause.desenharBotao();
    }
  	
    delay(1000);
  }
/*=====================================================================================================*/
//MULTIPLAYER 3D
  	else if(estadoAtual == JOGO_MULTIPLAYER3D){
      int linha, coluna, flagBotaoPausa=0;
      TSPoint p;
      tupla coord;
      if(newGame){
        resetarVariaveis();
        matrizEmBranco3D(hash_3D);
        desenharJogoDaVelha3D(tft); // mudar para 
        turn = 1;
      }

      else{
        desenharJogoDaVelha3D(tft);
        desenharJogoSalvo3D(hash_3D, tft);
      }

      while(check_winner_3D(hash_3D) == -1 && cont != 27 && flagBotaoPausa == 0){
        p = waitTouch(ts);
        Serial.println(p.x);
        Serial.println(p.y);
        if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
          //Alterar o estado
          //estadoAtual = MENU_PAUSE;
          flagBotaoPausa = 1;
  		  }
        coord = transformaTouch(p.x,p.y);
        if(turn == 2){
          if(valid_play3D(hash_3D,coord.i, coord.j, coord.k)){
            desenhaJogadas3D(&tft,coord.i,coord.j, coord.k,turn);
            hash_3D[coord.k][coord.i][coord.j] = turn;  
            turn = 1;
          }         
        }
        else if (turn == 1){ 
          if(valid_play3D(hash_3D,coord.i, coord.j, coord.k)){
            desenhaJogadas3D(&tft,coord.i,coord.j, coord.k,turn);
            hash_3D[coord.k][coord.i][coord.j] = turn;   
            turn = 2;  
          }        
      }
    }

    if(flagBotaoPausa==0){
      estadoAtual = MENU_INICIAL;
      //Alguem venceu, imprime quem
      limparTela(tft);
      tft.setCursor (45, 80);
      tft.setTextSize (2);
      tft.setTextColor(WHITE);
      switch (check_winner_3D(hash_3D))
      {
      case 0:
        tft.println("EMPATE!");
        break;
      case 1:
        tft.println("JOGADOR 2 VENCEU!");
        break;
      case 2:
        tft.println("JOGADOR 1 VENCEU!");
      }
      resetarVariaveis();
      matrizEmBranco3D(hash_3D); 
    }
    else{
      estadoAtual = MENU_PAUSE;
      botaoPause3D.setCor(GREEN);
      botaoPause3D.desenharBotao();
    }
      delay(1000);
  }
/*=====================================================================================================*/
	else if(estadoAtual == JOGO_SINGLEPLAYER3D){
		int linha, coluna, matriz, flagBotaoPausa=0;
		TSPoint p;
		tupla coord;
		tupla aiPlay;
		if(newGame){
			resetarVariaveis();
			matrizEmBranco3D(hash_3D);
			desenharJogoDaVelha3D(tft); // mudar para 
			//turn = AI;
      /*srand(time(NULL));
			coluna = rand()%3;
			linha = rand()%3;
      matriz = rand()%3;
			hash_3D[matriz][linha][coluna] = AI;
			desenhaJogadas3D(&tft,matriz, linha, coluna, AI);*/
			turn = 2;
			//cont++;
		}


    else{
			desenharJogoDaVelha3D(tft);
			desenharJogoSalvo3D(hash_3D, tft);
     	}
		while(check_winner_3D(hash_3D) == -1 && cont != 27 && flagBotaoPausa == 0){
      Serial.println(turn);
			if(turn == AI){
				aiPlay = bestPlay3D(hash_3D);
        hash_3D[aiPlay.k][aiPlay.i][aiPlay.j] = AI;
        Serial.print("aiPlay.i: ");
        Serial.println(aiPlay.i);
        Serial.print("aiPlay.j: ");
        Serial.println(aiPlay.j);
        Serial.print("aiPlay.k: ");
        Serial.println(aiPlay.k);
        desenhaJogadas3D(&tft,aiPlay.i,aiPlay.j, aiPlay.k,turn);
        turn = 2;
        cont++;
			}
			else if (turn == 2){ 
        p = waitTouch(ts);
        if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
          //Alterar o estado
          //estadoAtual = MENU_PAUSE;
          flagBotaoPausa = 1;
        }
			  coord = transformaTouch(p.x,p.y);
				if(valid_play3D(hash_3D,coord.i, coord.j, coord.k)){
					desenhaJogadas3D(&tft,coord.i,coord.j, coord.k,2);
					hash_3D[coord.k][coord.i][coord.j] = 2;   
					turn = AI;  
					cont++;
				}        
      }
		}
		if(flagBotaoPausa==0){
			estadoAtual = MENU_INICIAL;
			//Alguem venceu, imprime quem
			limparTela(tft);
			tft.setCursor (45, 80);
			tft.setTextSize (2);
			tft.setTextColor(WHITE);
			switch (check_winner_3D(hash_3D))
			{
			case 0:
				tft.println("EMPATE!");
				break;
			case 1:
				tft.println("JOGADOR  VENCEU!");
				break;
			case 2:
				tft.println("EU VENCI!");
			}
      resetarVariaveis();
			matrizEmBranco3D(hash_3D); 
		}else{
			estadoAtual = MENU_PAUSE;
			botaoPause3D.setCor(GREEN);
      botaoPause3D.desenharBotao();
		}
		delay(1000);
	}
/*=====================================================================================================*/
//Pause
  else if(estadoAtual == MENU_PAUSE){
  	//Desenhar o menu de pause
  	MenuPause _menuPause(BLACK,&tft,true,"PAUSE");
  	_menuPause.desenharMenu();

  	//Esperar o clique
  	while(true){
  		TSPoint p = waitTouch(ts);
  		if(p.x < 250 && p.x > 70){
  			//Botao REINICIAR
  			if(p.y > 220 && p.y < 310){
  				//Basta reiniciar as variaveis e alterar o estado
          _menuPause.ligaBotao(1);
  				resetarVariaveis();
  				matrizEmBranco(hash);
  				if(single == 1){
            if(tresD)
  					  estadoAtual = JOGO_SINGLEPLAYER3D;
            else
              estadoAtual = JOGO_SINGLEPLAYER2D;
          }
  				else{
  					if(tresD)
  					  estadoAtual = JOGO_MULTIPLAYER3D;
            else
              estadoAtual = JOGO_MULTIPLAYER2D;
          }  
  				break;
  			}
  			//Botão SAIR
  			else if(p.y > 340 && p.y < 430){
  				//Trocar a cor do botão
          _menuPause.ligaBotao(2);
  				//Alterar o estado
  				estadoAtual = MENU_INICIAL;
  				resetarVariaveis();
  				matrizEmBranco(hash);
          matrizEmBranco3D(hash_3D);
  				break;
  			}

  			//Botão retornar (volta o jogo com todas as jogadas já feitas)
  			else if(p.y > 100 && p.y < 190){
  				//não é um novo jogo
  				newGame = 0;
          _menuPause.ligaBotao(0);
  				//Basta alterar o estado, pq o hash não foi alterado
  				if(single){
            if(tresD)
              estadoAtual = JOGO_SINGLEPLAYER3D;
            else
              estadoAtual = JOGO_SINGLEPLAYER2D;
          }
  				else{
            if(tresD)
              estadoAtual = JOGO_MULTIPLAYER3D;
            else
              estadoAtual = JOGO_MULTIPLAYER2D;
          } 
  				break;
  			}
  		}

  	}
  }
}