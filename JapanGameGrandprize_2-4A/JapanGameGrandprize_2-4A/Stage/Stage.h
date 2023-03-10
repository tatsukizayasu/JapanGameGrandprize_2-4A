#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>
#include "StageBuilder/StageBuilder.h"

#define CHIP_SIZE	40

class Player;

class Stage_Element;

class Stage
{
private:

	//オブジェクト変数
	Player* player;
	Stage_Element* element;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//マップ配列データ
	std::vector<std::vector<int>> map_data;

	//背景画像
	int background_images;
	//ブロック画像
	int block_images[110];

	//当たったオブジェクトの座標	構造体
	POINT collision_chip;

	//当たっている方向		構造体
	//X[右:1, -左:-1], Y[上:1, 下:-1]
	POINT collision_dir;

	//当たっている方向	(値渡し用)	構造体
	POINT collision_dir_w;
protected:

	//MapChipオブジェクト
	std::vector<MapChip*> mapchip;
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
	/// StageクラスにPlayerオブジェクトを渡すSetter
	/// </summary>
	/// <param name = "*player">Playerオブジェクトポインタ</param>
	void SetPlayer(Player *player) { this->player = player; }

	/// <summary>
	/// マップサイズのGeter
	/// </summary>
	/// <returns>構造体型：マップサイズ</returns>	
	POINT GetMapSize(void) const
	{ 
		POINT mapsize{ map_data.at(0).size(),map_data.size() }; 
		return mapsize; 
	}

	/// <summary>
	/// マップチップオブジェクトのGetter
	/// </summary>
	/// <returns>ベクター型(MapChipオブジェクト型)：MapChip</returns>	
	/// ※全要素をループして使わないこと
	std::vector<MapChip*> GetMapChip() const { return mapchip; };

	/// <summary>
	/// **プレイヤーとステージの当たり判定用**
	/// 当たったマップチップの方向のGetter
	/// </summary>
	/// <returns>POINT型(構造体型) X[右:1, -左:-1], Y[上:1, 下:-1]</returns>	
	const POINT GetCollision_Chip() 
	{ 
		POINT w = collision_dir_w;  collision_dir_w = { 0, 0 };
		return w;
	}

	/// <summary>
	/// **プレイヤーとステージの当たり判定用**
	/// 当たったマップチップ座標のGetter
	/// </summary>
	/// <returns>POINT型(構造体型) X, Y</returns>	
	const POINT GetCollision_Chip_Location() 
	{ 
		POINT w = collision_chip;  collision_chip = { 0, 0 };
		return w;
	}
};