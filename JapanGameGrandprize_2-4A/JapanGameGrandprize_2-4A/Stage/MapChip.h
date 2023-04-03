#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f

class MapChip :
	public BoxCollider
{
public:

	//コンストラクタ
	MapChip();
	//コンストラクタ
	MapChip(const int* p_image, Location location, Area area);
	//デストラクタ
	virtual ~MapChip();
	//更新
	virtual void Update();
	//描画
	virtual void Draw() const;

	/// <summary>
	/// 当たり判定範囲のSetter
	/// </summary>
	void SetArea(Area set_area)
	{
		area.height = set_area.height;
		area.width = set_area.width;
	}

	/// <summary>
	/// 画像のSetter
	/// </summary>
	void SetImage(int image) 
	{
		this->image = image;
	}
protected:

	
	int image;
	Area image_size;
	float ex_rate;
};