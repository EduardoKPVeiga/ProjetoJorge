/*
* Um gerenciador de estados primitivo
*/
#pragma once
#include "LogicaJogo.h"
#include "MenuPause.h"
#include "MenuInicial.h"
#include "MenuEscolhaJogadores.h"
#include "Botao.h"
#include "Jogo2D.h"
#include "Jogo3D.h"
MenuInicial _menuInicial(BLACK, &tft, true, "ESCOLHA O MODO DE JOGO");
MenuEscolhaJogadores _menuEscolhaJogadores(BLACK, &tft, true, "ESCOLHA N° DE JOGADORES");
MenuPause _menuPause(BLACK,&tft,true,"PAUSE");
Jogo2D jogo2D;
Jogo3D jogo3D;
void GerenciarEstados(){
/*=====================================================================================================*/
//MENU INICIAL
	if(estadoAtual == MENU_INICIAL){
		//Desenha o menu inicial
		Menu* menuInicialPtr = dynamic_cast<Menu*>(&_menuInicial);
    menuInicialPtr->desenharMenu();
    int ativo;
    int leitura = analogRead(A15);
    int input = onRange(leitura);
    TSPoint p;
    while(input != 5 && ((p.z < MINPRESSURE || p.z > MAXPRESSURE))){
      
      p = ts.getPoint();
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      leitura = analogRead(A15);
      
      input = onRange(leitura);
      //botao apertado é cima ou baixo
      if(input == 2 || input == 3){
        delay(200);
        menuInicialPtr->trocaBotao(input);
      }
    }
    if(input!=5){
      p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
      p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
      if(p.x >70 && p.x < 270 ){
        if(p.y > 120 && p.y < 210){
          ativo = 0;
          newGame = 1;
          estadoAtual = MENU_ESCOLHA_JOGADORES;
          menuInicialPtr->ligaBotao(ativo);
        }      
        else if(p.y > 240 && p.y < 330){
          ativo = 1;
          newGame = 1;
          estadoAtual = MENU_ESCOLHA_JOGADORES;
          menuInicialPtr->ligaBotao(ativo);
        }
      }
    }
    if(input == 5){
      ativo = menuInicialPtr->indexBotaoAtivo();
      newGame = 1;
      estadoAtual = MENU_ESCOLHA_JOGADORES;
      menuInicialPtr->ligaBotao(ativo);
    }
    if (ativo == 0)
      tresD = 0;
    //Faz o botão clicado trocar de cor
    else if(ativo == 1)
      tresD = 1;
    
    delay(100); 
  }
/*=====================================================================================================*/
  else if(estadoAtual == MENU_ESCOLHA_JOGADORES){
    //Desenha o menu inicial	
  	Menu* menuJogPtr = dynamic_cast<Menu*>(&_menuEscolhaJogadores);
	  menuJogPtr->desenharMenu();
    int leitura = analogRead(A15);
    int input = onRange(leitura);
    int ativo;
    TSPoint p;
    while(input != 5 && ((p.z < MINPRESSURE || p.z > MAXPRESSURE))){
      
      p = ts.getPoint();
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      leitura = analogRead(A15);
      
      input = onRange(leitura);
      //botao apertado é cima ou baixo
      if(input == 2 || input == 3){
        delay(200);
        menuJogPtr->trocaBotao(input);
  
      }
    }
    if(input == 5){
      ativo = menuJogPtr->indexBotaoAtivo();
      menuJogPtr->ligaBotao(ativo);
      if(ativo == 0){
        single = 1;
        if(tresD)
            estadoAtual = JOGO_SINGLEPLAYER3D;
        else
          estadoAtual = JOGO_SINGLEPLAYER2D;
      }
      else if(ativo == 1){
        single = 0;
        if(tresD)
          estadoAtual = JOGO_MULTIPLAYER3D;
        else
          estadoAtual = JOGO_MULTIPLAYER2D;
      }
      else if(ativo == 2){
        estadoAtual = MENU_INICIAL;
      }
    }
    if(input!=5){
      p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
      p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
      if(p.x >70 && p.x < 270 ){
        if( p.y > 100 && p.y < 190){
          single = 1;
          if(tresD)
            estadoAtual = JOGO_SINGLEPLAYER3D;
          else
            estadoAtual = JOGO_SINGLEPLAYER2D;
          menuJogPtr->ligaBotao(0);
        }      
        else if(p.y > 220 && p.y < 310){
          single = 0;
          if(tresD)
            estadoAtual = JOGO_MULTIPLAYER3D;
          else
            estadoAtual = JOGO_MULTIPLAYER2D;
          menuJogPtr->ligaBotao(1);
        }
        else if(p.y >340 && p.y < 430){
          estadoAtual = MENU_INICIAL;
          menuJogPtr->ligaBotao(2);
        }
      }
    }
    delay(100);
  }

/*=====================================================================================================*/
  //JOGO SINGLEPLAYER2D
	else if(estadoAtual == JOGO_SINGLEPLAYER2D){
    	Serial.println("Case 2");
    //inicia os botoes selecionados do jogo
    jogo2D.hashBotao[9]->setCor(RED);
    jogo2D.hashBotao[9]->setAtivo(true);
    jogo2D.hashBotao[9]->desenhaSelecionado();
    for (int i = 0; i < 9; i++){
      jogo2D.hashBotao[i]->setAtivo(false);
    }
		int linha, coluna,flagBotaoPausa=0; //variaveis auxiliares
    Coordenada coord;
		if(newGame){
      		//resetar as variáveis
			resetarVariaveis();
			matrizEmBranco(hash);
      jogo2D.zeraHash();
      jogo2D.DesenhaHash();
      srand(time(NULL));

			//desenharJogoDaVelha(tft);
      
			//Aqui é o caso SINGLEPLAYER, então é preciso definir onde a MÁQUINA vai jogar
			//Vamos assumir que sempre será um novo jogo, nós definimos que a máquina sempre joga primeiro
			turn = 1;
			coluna = rand()%3;
			linha = rand()%3;
			hash[linha][coluna] = AI;
			jogo2D.JogodaVelha[linha][coluna]->setJogada(AI);
			turn = 2;
			cont++;
		}
    //Caso não seja um novo jogo
		else{
			jogo2D.DesenhaHash();
		}

		
		while(check_winner(hash) == -1 && cont < 9){
			//Se for a vez da máquina
			if(turn == 1){
				tupla aiPlay = bestPlay(hash);
				linha = aiPlay.i;
				coluna = aiPlay.j;
				hash[linha][coluna] = AI;
				//delay(250);
        jogo2D.JogodaVelha[linha][coluna]->setJogada(AI);
				desenharJogada(linha, coluna, turn, tft);
				turn = 2;
				cont++; 				
			}
			//Se for a vez do player
			else{
				int ativo;
        int leitura = analogRead(A15);
        int input = onRange(leitura);
        TSPoint p;
        while(input != 5 && ((p.z < MINPRESSURE || p.z > MAXPRESSURE))){
   
          p = ts.getPoint();
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);

          leitura = analogRead(A15);          
          input = onRange(leitura);
          //botao apertado é cima ou baixo
          if(input !=0 && input != 5){
            jogo2D.setSelecionado(input);
          }
        }
        if (input == 5){
          coord = jogo2D.getCoords();
          if(coord.x == -1){
            flagBotaoPausa=1;
					  break;
          }
        }
				//Checar botão de pausa
        else{
          p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
          p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
          if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
            flagBotaoPausa=1;
            break;
          }
          coord = coordenadaHash(p.x, p.y);
        }

				linha = coord.y;
				coluna = coord.x;
				//É preciso saber se a posição clicada é válida
				if(valid_play(hash, linha, coluna)){
					hash[linha][coluna] = 2;
					jogo2D.JogodaVelha[linha][coluna]->setJogada(turn);
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
      jogo2D.setAtivo(9);
      jogo2D.hashBotao[9]->setCor(GREEN);
      jogo2D.hashBotao[9]->desenhaSelecionado();
      jogo2D.hashBotao[9]->desenharBotao();
      
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
    Coordenada coord;
    int linha, coluna, flagBotaoPausa=0;

    //inicia os botoes selecionados do jogo
    jogo2D.hashBotao[9]->setCor(RED);
    jogo2D.hashBotao[9]->setAtivo(true);
    jogo2D.hashBotao[9]->desenhaSelecionado();
    for (int i = 0; i < 9; i++){
      jogo2D.hashBotao[i]->setAtivo(false);
    }
  	if(newGame){
  		resetarVariaveis();
  		matrizEmBranco(hash);
		  jogo2D.zeraHash();

  	}
    jogo2D.DesenhaHash();

  	while(check_winner(hash) == -1 && cont < 9){
  		//Assumindo sempre um novo jogo
  		//Receber a entrada 
      int ativo;
      int leitura = analogRead(A15);
      int input = onRange(leitura);
      TSPoint p;
      while(input != 5 && ((p.z < MINPRESSURE || p.z > MAXPRESSURE))){
  
        p = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        leitura = analogRead(A15);          
        input = onRange(leitura);
        //botao apertado é cima ou baixo
        if(input !=0 && input != 5){
          jogo2D.setSelecionado(input);
        }
      }
      if (input == 5){
        coord = jogo2D.getCoords();
        if(coord.x == -1){
          flagBotaoPausa=1;
          break;
        }
      }
      //Checar botão de pausa
      else{
        p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
        p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
        if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
          flagBotaoPausa = 1;
          break;
        }
        coord = coordenadaHash(p.x, p.y);
      }

  		linha = coord.y;
  		coluna = coord.x;
     
  		//Analisa se o ponto é válido e desenha caso for
  		if(turn == 1){
  			if(valid_play(hash, linha, coluna)){
  				hash[linha][coluna] = 1;
  				jogo2D.JogodaVelha[linha][coluna]->setJogada(turn);
  				turn = 2;
  				cont++;
  			}
  			else
  				Serial.println("Invalid play!");
  		}
  		else{
  			if(valid_play(hash, linha, coluna)){
  				hash[linha][coluna] = 2;
  				jogo2D.JogodaVelha[linha][coluna]->setJogada(turn);
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
      jogo2D.setAtivo(9);
      jogo2D.hashBotao[9]->setCor(GREEN);
      jogo2D.hashBotao[9]->desenhaSelecionado();
      jogo2D.hashBotao[9]->desenharBotao();
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
        jogo3D.zeraVariaveis();
        resetarVariaveis();
        matrizEmBranco3D(hash_3D);
        jogo3D.desenhaHash();
        turn = 1;
      }
      else{
        jogo3D.desenhaHash();
      }
      jogo3D.pause->setCor(RED);
      jogo3D.pause->desenharBotao();

      while(check_winner_3D(hash_3D) == -1 && cont != 27 && flagBotaoPausa == 0){
        int ativo;
        int leitura = analogRead(A15);
        int input = onRange(leitura);
        TSPoint p;
        input = -1;
        while(input != 5 && ((p.z < MINPRESSURE || p.z > MAXPRESSURE))){
    
          p = ts.getPoint();
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);

          leitura = analogRead(A15);          
          input = onRange(leitura);
          //botao apertado é cima ou baixo
          if(input !=0 && input != 5){
            jogo3D.setSelecionado(input);
          }
        }
        if (input == 5){
          coord = jogo3D.getCoords();
          if(coord.i == -1){
            flagBotaoPausa=1;
            break;
          }
        }
      //Checar botão de pausa
      else{
        p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
        p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
        if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
          flagBotaoPausa = 1;
          break;
        }
        coord = transformaTouch(p.x, p.y);
      }
      
      if(turn == 2){
        if(valid_play3D(hash_3D,coord.i, coord.j, coord.k)){
          jogo3D.setJogada(coord.k,coord.i,coord.j,turn);
          hash_3D[coord.k][coord.i][coord.j] = turn;  
          turn = 1;
        }         
      }
      else if (turn == 1){ 
        if(valid_play3D(hash_3D,coord.i, coord.j, coord.k)){
          jogo3D.setJogada(coord.k,coord.i,coord.j,turn);
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
      jogo3D.pause->setCor(GREEN);
      jogo3D.pause->setAtivo(false);
      jogo3D.pause->desenharBotao();
      jogo3D.hashTresD[0][0][0]->ativo = true;
    }
      delay(1000);
  }
/*=====================================================================================================*/
	else if(estadoAtual == JOGO_SINGLEPLAYER3D){
		int linha, coluna, flagBotaoPausa=0;
    TSPoint p;
    tupla coord;
    tupla aiPlay;
    if(newGame){
      jogo3D.zeraVariaveis();
      resetarVariaveis();
      matrizEmBranco3D(hash_3D);
      jogo3D.desenhaHash();
      turn = 1;
    }
    else{
      jogo3D.desenhaHash();
    }
    jogo3D.pause->setCor(RED);
    jogo3D.pause->desenharBotao();
      
		while(check_winner_3D(hash_3D) == -1 && cont != 27 && flagBotaoPausa == 0){
      Serial.println(turn);
			if(turn == AI){
				aiPlay = bestPlay3D(hash_3D);
        hash_3D[aiPlay.k][aiPlay.i][aiPlay.j] = AI;
        desenhaJogadas3D(&tft,aiPlay.i,aiPlay.j, aiPlay.k,turn);
        turn = 2;
        cont++;
			}
			else if (turn == 2){ 
        int ativo;
        int leitura = analogRead(A15);
        int input = onRange(leitura);
        TSPoint p;
        input = -1;
        while(input != 5 && ((p.z < MINPRESSURE || p.z > MAXPRESSURE))){
          p = ts.getPoint();
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);

          leitura = analogRead(A15);          
          input = onRange(leitura);
          //botao apertado é cima ou baixo
          if(input !=0 && input != 5){
            jogo3D.setSelecionado(input);
          }
        }
        if (input == 5){
          coord = jogo3D.getCoords();
          if(coord.i == -1){
            flagBotaoPausa = 1;
            break;
          }
        }
      //Checar botão de pausa
        else{
          p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
          p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
          if(p.x >= (205) && p.x <= (295) && p.y >=25 && p.y<=70){
            flagBotaoPausa = 1;
            break;
          }
          coord = transformaTouch(p.x, p.y);
        }
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
				tft.println("Jogador Venceu!");
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
    Menu* menuPausePtr = dynamic_cast<Menu*>(&_menuPause);

  	menuPausePtr->desenharMenu();
    int leitura = analogRead(A15);
    int input = onRange(leitura);
    int ativo;
    TSPoint p;
    while(input != 5 && ((p.z < MINPRESSURE || p.z > MAXPRESSURE))){
      
      p = ts.getPoint();
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      leitura = analogRead(A15);
      
      input = onRange(leitura);
      Serial.println(input);
      //botao apertado é cima ou baixo
      if(input == 2 || input == 3){
        delay(200);
      	menuPausePtr->trocaBotao(input);
      }
    }
    if(input == 5){
      ativo = menuPausePtr->indexBotaoAtivo();
      switch(ativo){
        case 0:
          newGame = 0;
          menuPausePtr->ligaBotao(0);
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
        case 1:
          //Basta reiniciar as variaveis e alterar o estado
          menuPausePtr->ligaBotao(1);
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
        case 2:
          //Trocar a cor do botão
          menuPausePtr->ligaBotao(2);
  				//Alterar o estado
  				estadoAtual = MENU_INICIAL;
  				resetarVariaveis();
  				matrizEmBranco(hash);
          matrizEmBranco3D(hash_3D);
  				break;          
      }
    }
  	//Esperar o clique
    else if(input != 5){
      p.x = map(p.x, TS_LEFT, TS_RT, 320,0);
      p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
  		if(p.x < 250 && p.x > 70){
  			//Botao REINICIAR
  			if(p.y > 220 && p.y < 310){
  				//Basta reiniciar as variaveis e alterar o estado
          menuPausePtr->ligaBotao(1);
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
  			}
  			//Botão SAIR
  			else if(p.y > 340 && p.y < 430){
  				//Trocar a cor do botão
          menuPausePtr->ligaBotao(2);
  				//Alterar o estado
  				estadoAtual = MENU_INICIAL;
  				resetarVariaveis();
  				matrizEmBranco(hash);
          matrizEmBranco3D(hash_3D);
  			}

  			//Botão retornar (volta o jogo com todas as jogadas já feitas)
  			else if(p.y > 100 && p.y < 190){
  				//não é um novo jogo
  				newGame = 0;
          menuPausePtr->ligaBotao(0);
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
  			}
  		}
  	}
  }
}