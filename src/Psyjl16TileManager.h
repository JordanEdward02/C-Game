#pragma once
#include "TileManager.h"

#define EMPTY 0
#define SUGAR 1
#define WALL 2


class Psyjl16TileManager :
    public TileManager
{
public:
    Psyjl16TileManager()
        : TileManager(100, 100, 15, 10)
    {
        maxSugar = 0;
        myMap = new int* [15];
        for (int i = 0; i < 15; i++) {
            myMap[i] = new int[10]();
        }
    }
    ~Psyjl16TileManager() {
        for (int i = 0; i < 15; i++) {
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
};

