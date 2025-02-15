#pragma once
#include "Stage_Element_Base.h"

class Element_Barricade : public Stage_Element_Base
{
public:
	enum class DIRECTION {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		CENTER
	};

private:
	
	DIRECTION direction;

public:


	//コンストラクタ
	Element_Barricade(short type, Resource resource, Location location, Area area, Area margin_area, DIRECTION direction);
	//デストラクタ
	~Element_Barricade();
	//更新
	void Update(Player* player) override;

};