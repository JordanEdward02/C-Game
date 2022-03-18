#pragma once
#include "BaseEngine.h"
#include "Psyjl16TileManager.h"
#include "MyCharacter.h"
#include "MyEnemy.h"
#include "MyBasicButton.h"
#include "MyToggleButton.h"
#include "MyTextBar.h"
#include "BaseState.h"
#include "PlayState.h"
#include "WinState.h"
#include "LoseState.h"
#include "MenuState.h"
#include "PauseState.h"



#define STARTGAME_STATE 1
#define MENU_STATE 2
#define LOSE_STATE 3
#define WIN_STATE 4
#define PAUSE_STATE 5

class Psyjl16Engine :
    public BaseEngine
{
public:
    Psyjl16Engine()
        :currentState(MENU_STATE)
        ,myState(nullptr)
    {
        myState = new MenuState(this);
    }
    ~Psyjl16Engine() {
        delete myState;
    }
    void virtSetupBackgroundBuffer();
    void virtMouseDown(int iButton, int iX, int iY);
    void virtKeyDown(int iKeyCode);
    void virtDrawStringsOnTop();
    Psyjl16TileManager& getTileManager() { return tm; }
    int virtInitialiseObjects();
    void globalRestart(int);
    void virtPreDraw();
    bool checkFinish();
private:
    Psyjl16TileManager tm;
    int currentState;
    BaseState* myState;

};

