#pragma once
#include <map>
class MapChip
{
private:

	struct MapData {
		int column;
		int line;
		int** map;
		MapData() {
			column = 50;
			line = 25;
			map = nullptr;
		}
	};

	std::map<const char*, MapData*> mapDatas;
	std::map<const char*, int> textureHandles;
	const int kBlockSize = 32;

public:
	MapChip();
	~MapChip();
	void MapDataLoad(const char* filePath,const char* tag);
	void Draw(const char* tag);
};