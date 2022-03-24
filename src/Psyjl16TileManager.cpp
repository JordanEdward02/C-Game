#include "header.h"
#include "Psyjl16TileManager.h"


using namespace std;
void Psyjl16TileManager::virtDrawTileAt(
	BaseEngine* pEngine, // We don't need this but maybe a student will so it is here to use if needed
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY); // which was set to result of rand()
	unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) // red
		+ (unsigned int)((iMapValue & 0xf0) << 8) // green
		+ (unsigned int)((iMapValue & 0xf) << 4); // blue

	switch (myMap[iMapX][iMapY]) {
	case SUGAR:
	{
		pSurface->drawRectangle(
			iStartPositionScreenX, iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			0xFFFFFF
		);
		char buf[64];
		sprintf(buf, "SUGAR");
		pSurface->drawScalableString(iStartPositionScreenX + 2, iStartPositionScreenY + 30,
			buf, 0x000000, NULL);
		break;
	}
	case WALL:
	{
		pSurface->drawRectangle(
			iStartPositionScreenX, iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			0x000000
		);
		break;
	}
	}

}


void Psyjl16TileManager::reset() {
	maxSugar = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0 || i == 14 || j == 0 || j == 9) {
				myMap[i][j] = WALL;
			}
			else {
				if (rand() % 30 == 0) {
					myMap[i][j] = SUGAR;
					maxSugar += 1;
				}
				else {
					myMap[i][j] = EMPTY;
				}
			}
		}
	}
	TotalSugar = 0;
}