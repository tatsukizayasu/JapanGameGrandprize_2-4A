#pragma once
#include "Stage_Element_Base.h"

class Element_DamageWall : public Stage_Element_Base
{
private:

public:

	//コンストラクタ
	Element_DamageWall(MapChip* mapchip, int* image);
	//デストラクタ
	~Element_DamageWall();
	//更新
	void Update(Player *player);
	//描画
	void Draw() const;


};