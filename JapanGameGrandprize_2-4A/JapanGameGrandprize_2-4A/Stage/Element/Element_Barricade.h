#pragma once
#include "Stage_Element_Base.h"
class Element_Barricade : public Stage_Element_Base
{
private:
	enum class DIRECTION {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		CENTER
	} direction;

public:

	//コンストラクタ
	Element_Barricade(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	//デストラクタ
	~Element_Barricade();
	//更新
	void Update(Player* player) override;



};