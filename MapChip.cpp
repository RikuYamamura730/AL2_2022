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

	// �s�Ɨ�̐����J�E���g
	while (!ifs.eof()) {
		getline(ifs, line);
		l++;
	}
	// �}�b�v�f�[�^�ɍs���Ɨ񐔂�ۑ�
	mapData->column = (int)std::count(line.begin(), line.end(), ',');
	mapData->column += 1;
	mapData->line = l;

	// �ǂ݂��񂾃f�[�^���������m��
	mapData->map = (int**)malloc(sizeof(int*) * mapData->line);

	for (int i = 0; i < mapData->line; i++) {
		mapData->map[i] = (int*)malloc(sizeof(int) * mapData->column);
	}

	// �X�g���[���ʒu���J�n�ʒu�ɖ߂�
	ifs.seekg(0, ios_base::beg);

	//�}�b�v�ɏ�������
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
