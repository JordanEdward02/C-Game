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
		sprintf(buf, "s");
		pSurface->drawScalableString(iStartPositionScreenX + 8, iStartPositionScreenY + 3,
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
	case PLANT:
	{
		pSurface->drawLine(iStartPositionScreenX+7, iStartPositionScreenY+22, iStartPositionScreenX+25, iStartPositionScreenY+22, 0xeb8f34);
		plantSprite.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX+8, iStartPositionScreenY + 8, 16, 16, 0xff00e2);
		break;
	}
	case FIELD:
	{
		fieldSprite.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX + 8, iStartPositionScreenY + 8, 16, 16, 0xff00e2);
		break;
	}
	}

}


void Psyjl16TileManager::reset() {
	maxSugar = 0;
	ifstream inFile("LevelData.txt");
	string line;
	if (!inFile.is_open())
		return;
	//Reads past the first line which is just size params.
	getline(inFile, line);
	int pos = 0;
	int item;
	for (int i = 0; i < myHeight; i++) {
		int j = 0;
		if (getline(inFile, line)) {
			while ((pos = line.find(',')) != string::npos) {
				item = stoi(line.substr(0, pos));
				myMap[j++][i] = item;
				if (item == 1)
					maxSugar += 1;
				line.erase(0, pos + 1);
			}
			item = stoi(line);
			myMap[j++][i] = item;
			if (item == 1)
				maxSugar += 1;
		}
	}
	inFile.close();
	TotalSugar = 0;
}