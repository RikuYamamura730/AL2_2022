#include "MapChip.h"
#include <fstream>
#include <cassert>
#include <string>
#include <Novice.h>

using namespace std;

MapChip::~MapChip()
{
}

void MapChip::MapDataLoad(const char* filePath,const char* tag)
{
	string line;
	string mapDataString;
	ifstream ifs(filePath);
	MapData* mapData = new MapData();

	assert(ifs.is_open());
	int l = 0;

	// 行と列の数をカウント
	while (!ifs.eof()) {
		getline(ifs, line);
		l++;
	}
	// マップデータに行数と列数を保存
	mapData->column = (int)std::count(line.begin(), line.end(), ',');
	mapData->column += 1;
	mapData->line = l;

	// 読みこんだデータ分メモリ確保
	mapData->map = (int**)malloc(sizeof(int*) * mapData->line);

	for (int i = 0; i < mapData->line; i++) {
		mapData->map[i] = (int*)malloc(sizeof(int) * mapData->column);
	}

	// ストリーム位置を開始位置に戻す
	ifs.seekg(0, ios_base::beg);

	//マップに書き込み
	for (int y = 0; y < mapData->line; y++) {
		std::getline(ifs, mapDataString);
		mapDataString.erase(std::remove(mapDataString.begin(), mapDataString.end(), ','), mapDataString.end());
		for (int x = 0; x < mapData->column; x++) {
			int n = mapDataString[x] - '0';
			mapData->map[y][x] = n;
		}
	}

	mapDatas[tag] = mapData;
}

void MapChip::Draw(const char* tag) 
{
	for (int y = 0; y < mapDatas[tag]->line; y++) {
		for (int x = 0; x < mapDatas[tag]->column; x++) {
			Novice::DrawBox(x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize, 0.0f, WHITE, kFillModeSolid);
		}
	}
}
