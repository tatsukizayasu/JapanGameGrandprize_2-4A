#pragma once
#include "Stage_Element_Base.h"

class Element_DamageWall : public Stage_Element_Base
{
public:

	//コンストラクタ
	Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	//デストラクタ
	~Element_DamageWall();
	//更新
	void Update(Player *player) override;
};