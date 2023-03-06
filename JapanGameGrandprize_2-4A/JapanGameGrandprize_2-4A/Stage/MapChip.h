#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f
class Player;

class MapChip :
	public BoxCollider
{
private:

	//当たっている方向	構造体
	//X[右:1, -左:-1], Y[上:1, 下:-1]
	POINT collision_dir;


public:

	//コンストラクタ
	MapChip();
	//コンストラクタ
	MapChip(const int* p_image, Location location, Area area);
	//デストラクタ
	~MapChip();
	//更新
	void Update(Player* player);
	//描画
	virtual void Draw() const;

	const char* GetName() { return class_name; }


	/// <summary>
	/// **プレイヤーとステージの当たり判定用**
	/// 当たったマップチップ座標のGetter
	/// </summary>
	/// <returns>POINT型(構造体型) X[右:1, -左:-1], Y[上:1, 下:-1]</returns>	
	const POINT GetMapChip_Collision() {

		POINT w = collision_dir;

		collision_dir = { 0,0 };

		return w;
	}


protected:

	const char* class_name = "default";
	int image;
	Area image_size;
	float ex_rate;
};