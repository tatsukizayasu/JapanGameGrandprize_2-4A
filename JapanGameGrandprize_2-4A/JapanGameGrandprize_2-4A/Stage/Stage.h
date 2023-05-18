#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>
#include "StageBuilder/StageBuilder.h"
#include "Element/Stage_Element_Base.h"
#include <set>


#define CHIP_SIZE	40

class Player;

class EnemyBase;

class CameraWork;

class Stage_Element;

namespace Ground {
	const short STAGE01_BASE = 5;			//Stage1 足場ブロック
	const short STAGE01_UNDERGROUND = 4;			//Stage1 地中ブロック
}

struct ENEMY_LOCATION
{
	short id;
	Location location;
};

class Stage
{
private:

	//オブジェクト変数
	Player* player;
	Stage_Element* element;
	EnemyBase** enemy;
	CameraWork* camera_work;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	// オブジェクトのカメラワーク座標
	Location object_camera_work;

	// カメラワークの旧座標
	Location old_camera_work;

	

	//スポーン地点
	Location spawn_point;

	//中間地点
	Location halfway_point;

	//中間地点を取ったかのフラグ
	bool is_halfway_point;

	//マップ配列データ
	std::vector<std::vector<int>> map_data;

	//MapChipオブジェクト
	std::vector<MapChip*> mapchip;

	//エネミースポーン地点Location構造体
	std::vector<ENEMY_LOCATION> enemy_init_location;

	//エネミーのID
	std::set<short> enemy_id{ 200,201,202,203,204,205,206,207,208,209,210 };


	//背景画像
	int background_images;
	int block_images[50];
	int stage1_block_images[10];
	
	int bort_image;

	//ステージ足場ブロックのID
	std::set<short> stage_id_base{ Ground::STAGE01_BASE };

	//ステージ地中ブロックのID
	std::set<short> stage_id_underground{ Ground::STAGE01_UNDERGROUND };

	//ステージの番号
	short stage_num;

	//背景画像
	int background_image[3];
	//背景画像座標
	Location background_location;
	//背景画像RGB
	int backgraound_image_color[3];
	//背景ブレンド値
	int backgraound_blend;



protected:


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stage(short stage_num);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stage();

	/// <summary>
	/// ステージの更新
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// ステージ背景の更新
	/// </summary>
	void UpdateStageBackground(bool is_spawn_boss);

	/// <summary>
	/// ステージの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ステージ背景の描画
	/// </summary>
	void DrawStageBackground() const;

	/// <summary>
	/// オブジェクト 描画関数
	/// </summary>
	void DrawObject() const;

	/// <summary>
	/// オブジェクト カメラワーク
	/// </summary>
	void ObjectCameraWork(Player* player);

	/// <summary>
	/// ステージの読み込み
	/// </summary>
	void LoadMap(short stage_num);

	/// <summary>
	/// ステージの初期化
	/// </summary>
	void InitStage(void);

	/// <summary>
	/// 固定ブロックの追加
	/// </summary>
	/// <param name = "id">short型：ステージブロックID</param>
	/// <param name = "x">float型：座標X</param>
	/// <param name = "y">float型：座標Y</param>
	void AddFixedMapChip(short id, float x, float y);

	/// <summary>
	/// スポーン地点		Getter
	/// </summary>
	Location GetSpawnPoint() { return spawn_point; }

	/// <summary>
	/// 中間地点		Getter
	/// </summary>
	Location GetHalfwayPoint() { return halfway_point; }

	/// <summary>
	/// 中間地点を取ったかのフラグ		Getter
	/// </summary>
	bool IsHalfwayPoint() { return is_halfway_point; }

	/// <summary>
	/// StageクラスにPlayerオブジェクトを渡すSetter
	/// </summary>
	/// <param name = "*player">Playerオブジェクトポインタ</param>
	void SetPlayer(Player *player) { this->player = player; }

	/// <summary>
	/// StageクラスにEnemyオブジェクトを渡すSetter
	/// </summary>
	/// <param name = "*player">Playerオブジェクトポインタ</param>
	void SetEnemy(EnemyBase** enemy);

	/// <summary>
	/// StageクラスにCameraWorkオブジェクトを渡すSetter
	/// </summary>
	/// <param name = "*camera">CameraWorkオブジェクトポインタ</param>
	void SetCameraWork(CameraWork* camera) { this->camera_work = camera; }

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
	///	idは200番台
	/// </summary>
	/// <returns>ベクター型(ENEMY_LOCATION構造体型)</returns>	
	std::vector<ENEMY_LOCATION> GetEnemy_SpawnLocation() const { return enemy_init_location; }

	/// <summary>
	/// エレメントパラメータ設定関数
	/// </summary>
	void SetElement();

	short GetStageNum() { return stage_num; }
};