#include "header.h"

#include "MyScoreViewer.h"

using namespace std;
void MyScoreViewer::virtDrawTileAt(
    BaseEngine* pEngine,
    DrawingSurface* pSurface,
    int iMapX, int iMapY,
    int iStartPositionScreenX, int iStartPositionScreenY) const{
    
    int i = getMapXForScreenX(iStartPositionScreenX);
    int j = getMapYForScreenY(iStartPositionScreenY);
    if (myMap[j][i].empty())
        return;
    pSurface->drawFastString(iStartPositionScreenX + 2, iStartPositionScreenY + 30,
        myMap[j][i].c_str(), 0x000000, NULL);
}