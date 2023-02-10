#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include <vector>

#define MENU_NUM 3
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2

using namespace std;

class StageBuilder
{
private:
	SphereCollider* mouse;//判定のみ
	Location mouse_pos;
	//ブロック画像
	int block_images[100];
	vector<MapChip*> map_chips;

	int mode;

	int menu_cursor;
	char arrow[MENU_NUM];

public:
	//コンストラクタ
	StageBuilder();
	//デストラクタ
	~StageBuilder();
	//更新
	void Update();
	//描画
	void Draw()const;

	//メニューモードの更新
	void UpdateMenu();
	//ブラシモードの更新
	void UpdateBrush();
	//モデュレーションモードの更新
	void UpdateModulation();

	//マウスの更新
	void UpdateMouse();
	//メニューモードの描画
	void DrawMenu()const;
	//格子の描画
	void DrawFrame()const;

	//マップチップを作成する
	void MakeMapChip();

	//CSVファイルへの書き出し
	void SaveStage();
};

