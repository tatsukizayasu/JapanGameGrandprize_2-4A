#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include <vector>
using namespace std;

class StageBuilder
{
private:
	Location mouse_pos;
	//ブロック画像
	int block_images[100];
	vector<MapChip*> map_chips;

public:
	//コンストラクタ
	StageBuilder();
	//デストラクタ
	~StageBuilder();
	//更新
	void Update();
	//描画
	void Draw()const;

	//マウスの更新
	void MouseUpdate();
	//格子の描画
	void DrawFrame()const;

	//マップチップを作成する
	void MakeMapChip();
};

