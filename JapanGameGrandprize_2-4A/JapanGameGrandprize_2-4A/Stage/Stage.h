#pragma once
#include "MapChip.h"
#include <vector>

#include "StageBuilder/StageBuilder.h"

class Stage
{
private:
	//MapChipオブジェクト
	std::vector<MapChip*> mapchip;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//マップ配列データ
	std::vector<std::vector<int>> map_data;

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