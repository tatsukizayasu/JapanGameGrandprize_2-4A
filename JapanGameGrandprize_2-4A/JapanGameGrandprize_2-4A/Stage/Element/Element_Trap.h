#pragma once
#include "Stage_Element_Base.h"
class Element_Trap : public Stage_Element_Base
{
private:

	enum class STATE {
		NONE,		//なし
		EXPLOSION,	//爆発
		EXTINGUISHMENT	//消滅
	}state;

public:

	//コンストラクタ
	Element_Trap(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	//デストラクタ
	~Element_Trap();
	//更新
	void Update(Player* player) override;

	void Draw()const override;


};