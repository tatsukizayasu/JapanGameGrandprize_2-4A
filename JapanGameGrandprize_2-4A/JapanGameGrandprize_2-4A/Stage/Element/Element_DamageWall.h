#pragma once
#include "Stage_Element_Base.h"
#include <future>

class Element_DamageWall : public Stage_Element_Base
{
private:
	Player* player;
public:

	//コンストラクタ
	Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//デストラクタ
	~Element_DamageWall();
	//更新
	void Update(Player *player) override;
	////描画
	//void Draw() const override;

	void Damage(Player* player);


};