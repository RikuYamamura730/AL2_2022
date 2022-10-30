#include <Novice.h>
#include "Enemy.h"
#include <fstream>
#include <cassert>
#include <string>

const char kWindowTitle[] = "学籍番号";
const int kWindowWitdh = 800;
const int kWindowHeight = 800;
using namespace std;

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

int CountFileLine(const char* filePath);
int CountFileColumn(const char* filePath);
void LoadMapData(const char* filePath, MapData& map);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWitdh, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Enemy* enemy = new Enemy();

	/*int l = CountFileLine("mapSample.csv");
	int c = CountFileColumn("mapSample.csv");*/
	MapData mapData;


	LoadMapData("mapSample.csv", mapData);

#pragma region fscan_sによるマップデータ読みこむ
	//// 読みこんだデータ分メモリ確保
	//mapData.map = (int**)malloc(sizeof(int*) * mapData.line);

	//for (int i = 0; i < mapData.line; i++) {
	//	mapData.map[i] = (int*)malloc(sizeof(int) * mapData.column);
	//	if (mapData.map[i] == nullptr) {
	//		printf("メモリ確保失敗");
	//		exit(1);
	//	}
	//}

	//FILE* fp;
	//fopen_s(&fp, "mapSample.csv", "r");

	//for (int y = 0; y < mapData.line; y++) {
	//	for (int x = 0; x < mapData.column; x++) {
	//		fscanf_s(fp, "%d,", &mapData.map[y][x]);
	//	}
	//}

	//fclose(fp);
#pragma endregion

	int sx, sy;
	sx = 0;
	sy = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		enemy->Move();

		if (keys[DIK_LEFT]) {
			sx -= 10;
		}
		if (keys[DIK_RIGHT]) {
			sx += 10;
		}
		if (keys[DIK_UP]) {
			sy -= 10;
		}
		if (keys[DIK_DOWN]) {
			sy += 10;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int i = 0; i < mapData.line; i++) {
			for (int j = 0; j < mapData.column; j++) {
				if (mapData.map[i][j] == 1) {
					Novice::DrawBox(j * 32 + sx, i * 32 + sy, 32, 32, 0.0f, WHITE, kFillModeSolid);
				}
			}
		}

		enemy->Draw();



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
	free(mapData.map);
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}


int CountFileLine(const char* filePath) {
	int lineCount = 0;
	string line;
	ifstream ifs(filePath);

	assert(ifs.is_open());

	while (ifs) {
		getline(ifs, line);

		lineCount++;
		if (ifs.eof()) {
			break;
		}
	}
	int columnCount = (int)std::count(line.begin(), line.end(), ',');

	ifs.close();
	return lineCount;
}

int CountFileColumn(const char* filePath) {
	int columnCount = 0;
	string line;
	ifstream ifs(filePath);

	assert(ifs.is_open());

	getline(ifs, line);
	columnCount = (int)std::count(line.begin(), line.end(), ',');

	ifs.close();
	return columnCount + 1;
}

void LoadMapData(const char* filePath, MapData& mapData) {
	string line;
	string mapDataString;
	ifstream ifs(filePath);

	assert(ifs.is_open());
	int l = 0;

	// 行と列の数をカウント
	while (!ifs.eof()) {
		getline(ifs, line);
		l++;
	}
	// マップデータに行数と列数を保存
	mapData.column = (int)std::count(line.begin(), line.end(), ',');
	mapData.column += 1;
	mapData.line = l;

	// 読みこんだデータ分メモリ確保
	mapData.map = (int**)malloc(sizeof(int*) * mapData.line);

	for (int i = 0; i < mapData.line; i++) {
		mapData.map[i] = (int*)malloc(sizeof(int) * mapData.column);
	}

	// ストリーム位置を開始位置に戻す
	ifs.seekg(0, ios_base::beg);

	//マップに書き込み
	for (int y = 0; y < mapData.line; y++) {
		std::getline(ifs, mapDataString);
		mapDataString.erase(std::remove(mapDataString.begin(), mapDataString.end(), ','), mapDataString.end());
		for (int x = 0; x < mapData.column; x++) {
			int n = mapDataString[x] - '0';
			mapData.map[y][x] = n;
		}
	}
}