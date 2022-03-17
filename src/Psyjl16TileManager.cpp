#include "header.h"
#include "Psyjl16TileManager.h"

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
	case 1:
		pSurface->drawRectangle(
			iStartPositionScreenX, iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			0xFFFFFF
		);
		char buf[64];
		sprintf(buf, "SUGAR");
		pSurface->drawFastString(iStartPositionScreenX + 2, iStartPositionScreenY + 30,
			buf, 0x000000, NULL
		);
	}
}


void Psyjl16TileManager::reset() {
	maxSugar = 0;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 7; j++) {
			if (rand() % 30 == 0) {
				myMap[i][j] = 1;
				maxSugar += 1;
			}
			else {
				myMap[i][j] = 0;
			}
		}
	}
	TotalSugar = 0;

}