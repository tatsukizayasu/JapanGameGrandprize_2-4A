#pragma once
#include "Stage_Element_Base.h"

class Element_Wooden_Floor : public Stage_Element_Base
{
private:

	//元の画像
	int original_image;

	//元の当たり判定範囲
	Area original_collision;
public:

	//コンストラクタ
	Element_Wooden_Floor(short type, Resource resource, Location location, Area area);
	//デストラクタ
	~Element_Wooden_Floor();

	//更新
	void Update(Player* player) override;
};