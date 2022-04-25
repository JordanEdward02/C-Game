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
#include <fstream>
#include "CustomFilter.h"



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
    int virtInitialise();
    void virtSetupBackgroundBuffer();
    void virtMouseDown(int iButton, int iX, int iY);
    void virtKeyDown(int iKeyCode);
    void virtDrawStringsOnTop();
    Psyjl16TileManager& getTileManager() { return tm; }
    int virtInitialiseObjects();
    void globalRestart(int);
    void virtPreDraw();
    bool checkFinish();
    void setScale(int);
    void setOffset(int, int);
    int getScale();
    void virtMouseWheel(int, int, int, int);
    void upScale() {
        filterScale.upScale();
    };
    void downScale() {
        filterScale.downScale();
    };
    void virtMainLoopDoBeforeUpdate();
    void newBackground(DrawingSurface*);
    void copyAllBackgroundBuffer();
    int xOffset = 0;
    int yOffset = 0;
    CustomFilter& getFilter() {
        return filterScale;
    }
    void setBackgroundX(int);
    void setBackgroundY(int);
private:
    Psyjl16TileManager tm;
    int currentState;
    BaseState* myState;
    CustomFilter filterScale;
};

