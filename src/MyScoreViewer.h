#pragma once
#include "TileManager.h"
#include <fstream>

using namespace std;

class MyScoreViewer :
    public TileManager
{
public:
    MyScoreViewer()
        :TileManager(50,200,2,10)
    {
        ifstream inFile("Highscores.txt");
        string line;
        if (!inFile.is_open())
            return;
        myMap = new string* [10];
        for (int i = 0; i < 10; i++) {
            myMap[i] = new string[2];
        }
        for (int i = 0; i < 10; i++) {
            if (getline(inFile, line)) {
                for (int j = 0; j < 2; j++) {
                    if (j == 0) {
                        myMap[i][j] = line.substr(0, line.find(','));
                    }
                    else {
                        myMap[i][j] = line.substr(line.find(',') + 1, 20);
                    }
                }
            }
        }
        inFile.close();
    }

    ~MyScoreViewer() {
        for (int i = 0; i < 10; i++) {
            delete[] myMap[i];
        }
        delete[] myMap;
    }

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const ;


private:
    string** myMap;
};

