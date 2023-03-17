#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>
#include "StageBuilder/StageBuilder.h"
#include "Element/Stage_Element_Base.h"
#include <set>

#define CHIP_SIZE	40

class Player;

class Stage_Element;

class Stage
{
public:
	struct ENEMY_LOCATION {
		short id;
		float x;
		float y;
	};

private:

	//オブジェクト変数
	Player* player;
	Stage_Element* element;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	//マップ配列データ
	std::vector<std::vector<int>> map_data;


	//エネミースポーン地点Location構造体
	std::vector<ENEMY_LOCATION> enemy_init_location;

	//エネミーのID
	std::set<short> enemy_id{ 200,201,202,203,204,205,206,207,208,209,210 };

	//背景画像
	int background_images;
	//ブロック画像
	int block_images[110];


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
	std::vector<MapChip*> GetMapChip() const;

	/// <summary>
	/// ElementオブジェクトのGetter
	/// </summary>
	/// <returns>ベクター型(Stage_Element_Baseオブジェクト型)：Stage_Element_Base</returns>	
	/// ※全要素をループして使わないこと
	std::vector<Stage_Element_Base*> GetElement_MapChip() const;

	
	/// <summary>
	///エネミースポーンLocation構造体	Getter
	/// </summary>
	/// <returns>ベクター型(ENEMY_LOCATION構造体型)</returns>	
	std::vector<ENEMY_LOCATION> GetEnemy_SpawnLocation() const { return enemy_init_location; }
};