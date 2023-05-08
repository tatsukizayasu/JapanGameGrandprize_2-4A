#pragma once
#include "Stage_Element_Base.h"

class Element_Conveyor_Belt : public Stage_Element_Base
{
public:

	//コンストラクタ
	Element_Conveyor_Belt(short type, std::vector<int> images, Location location, Area area);
	//デストラクタ
	~Element_Conveyor_Belt();
	//更新
	void Update(Player* player) override;
};