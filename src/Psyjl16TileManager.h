#pragma once
#include "TileManager.h"
class Psyjl16TileManager :
    public TileManager
{
public:
    Psyjl16TileManager()
        : TileManager(100, 100, 13, 7)
    {
        maxSugar = 0;
        myMap = new int* [13];
        for (int i = 0; i < 13; i++) {
            myMap[i] = new int[7]();
        }
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 7; j++) {
                if (rand() % 30 == 0) {
                    myMap[i][j] = 1;
                    maxSugar += 1;
                }
            }
        }
    }
    ~Psyjl16TileManager() {
        for (int i = 0; i < 13; i++) {
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
        if (val == 0) {
            myMap[iX][iY] = val;
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

