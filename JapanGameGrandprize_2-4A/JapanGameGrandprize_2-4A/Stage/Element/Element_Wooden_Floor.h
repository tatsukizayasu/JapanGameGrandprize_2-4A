#pragma once
#include "Stage_Element_Base.h"


class Element_Wooden_Floor : public Stage_Element_Base
{
private:

	//元の当たり判定範囲
	Area original_collision;

public:

	//コンストラクタ
	Element_Wooden_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//デストラクタ
	~Element_Wooden_Floor();

	//更新
	void Update(Player* player) override;
	////描画
	//void Draw() const override;


};