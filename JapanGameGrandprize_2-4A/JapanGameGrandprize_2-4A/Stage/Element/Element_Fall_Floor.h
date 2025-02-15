#pragma once
#include "Stage_Element_Base.h"

class Element_Fall_Floor : public Stage_Element_Base
{
private:
	
	//点滅
	bool is_flash;

	//落下スピード
	float fall_speed;

	//増加分
	float increment;
	
	enum class STATE {
		NONE,		//なし
		WORKING,	//落ちる前
		FALL,		//落下
	} state;
public:

	//コンストラクタ
	Element_Fall_Floor(short type, Resource resource, Location location, Area area);
	//デストラクタ
	~Element_Fall_Floor();
	//更新
	void Update(Player* player) override;
};