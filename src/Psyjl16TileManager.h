#pragma once
#include "TileManager.h"
#include <fstream>

#define EMPTY 0
#define SUGAR 1
#define WALL 2
#define PLANT 3
#define FIELD 4

using namespace std;
class Psyjl16TileManager :
    public TileManager
{
public:
    Psyjl16TileManager()
        : TileManager(32, 32, 0, 0)
    {
        ifstream inFile("LevelData.txt");
        string line;
        if (!inFile.is_open())
            return;
        getline(inFile, line);
        myWidth = stoi(line.substr(0, line.find(',')));
        myHeight = stoi(line.substr(line.find(',')+1, 20));
        myMap = new int* [myWidth];
        for (int i = 0; i < myWidth; i++) {
            myMap[i] = new int[myHeight];
        }
        inFile.close();
        setMapSize(myWidth, myHeight);
        maxSugar = 0;
        fieldSprite = ImageManager::loadImage("images/Wheatfield.png", true);
        plantSprite = ImageManager::loadImage("images/Cactus.png", true);
    }
    ~Psyjl16TileManager() {
        for (int i = 0; i < myWidth; i++) {
            delete [] myMap[i];
        }
        delete [] myMap;
    }
    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;
    void setMyMap(int iX, int iY, int val) {
        if (val == EMPTY) {
            myMap[iX][iY] = EMPTY;
            TotalSugar += 1;
        }
    }
    int getMyMap(int iX, int iY) {
        if (iX > myWidth || iY > myHeight)
            return 0;
        return myMap[iX][iY];
    }
    int getSugar() {
        return TotalSugar;
    }
    void reset();
    bool isDone() {
        return !(maxSugar - TotalSugar);
    }
    int getTest() {
        return maxSugar;
    }
protected:
    int** myMap;
    int TotalSugar=0;
    int maxSugar=0;
    int myWidth = 0;
    int myHeight = 0;
    SimpleImage fieldSprite, plantSprite;
};

