#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>

#include "StageBuillder/StageBuilder.h"

#define CHIP_SIZE		40

class Player;

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
	int block_images[110];

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
	void Update(Player* player);
	/// <summary>
	/// ステージの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ステージの読み込み
	/// </summary>
	void LoadMap();

	/// <summary>
	/// マップサイズのGeter
	/// </summary>
	/// <returns>構造体型：マップサイズ</returns>	
	POINT GetMapSize(void) { POINT mapsize{ map_data.size(),map_data.at(0).size(), };  return mapsize; }
};