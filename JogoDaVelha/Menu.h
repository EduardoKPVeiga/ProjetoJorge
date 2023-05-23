/*
* Define um menu
*/

#pragma once
#include "Botao.h"

class Menu{
protected:
	int corMenu;
    MCUFRIEND_kbv* ptrTela;
    bool estadoDoMenu;
    Botao* listaBotoes[3];
    char tituloMenu[30];
    Botao* ptrBotao;
public:
	Menu(){}

    Menu(int _corMenu, MCUFRIEND_kbv* _ptrTela, bool _estadoDoMenu, const char* _tituloMenu  = ""):
        corMenu(_corMenu),
        ptrTela(_ptrTela),
        estadoDoMenu(_estadoDoMenu)      
        {
            strncpy(tituloMenu, _tituloMenu, 30);
            ptrBotao = nullptr;
            for (int i = 0; i < 3; i++){
                listaBotoes[i] = nullptr;}
        }

        ~Menu(){
            ptrBotao = nullptr;
        }

        virtual void desenharMenu() = 0;
        virtual void criaBotoes() = 0;
        void setEstadoDoMenu(bool _estadoDoMenu = false){
            estadoDoMenu = _estadoDoMenu;
        }
};