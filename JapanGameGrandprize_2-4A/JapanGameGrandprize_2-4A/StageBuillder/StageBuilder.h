#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include <vector>

class StageBuilder
{
private:
	Location mouse_pos;
	//ブロック画像
	int block_images[100];

public:
	//コンストラクタ
	StageBuilder();
	//デストラクタ
	~StageBuilder();
	//更新
	void Update();
	//描画
	void Draw()const;

	//マップチップを作成する
	MapChip* MakeMapChip();
};

