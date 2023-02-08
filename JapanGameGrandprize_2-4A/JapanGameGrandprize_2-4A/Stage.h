#pragma once
#include "MapChip.h"
#include <vector>

#include "StageBuillder/StageBuilder.h"

class Stage
{
private:
	//MapHipオブジェクト
	std::vector<MapChip*> mapchip;

#ifdef STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//背景画像
	int background_images;
	//ブロック画像
	int block_images[100];

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stage();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stage();
	/// <summary>
	/// ステージの更新
	/// </summary>
	void Update();
	/// <summary>
	/// ステージの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ステージの読み込み
	/// </summary>
	void LoadMap();
};

