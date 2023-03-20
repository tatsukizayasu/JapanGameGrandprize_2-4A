#include "Element_DamageWall.h"
#include "../Player.h"


Element_DamageWall::Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->area = area;
	this->type = type;
	
	this->images = images;

	anim_count = 0;
}

Element_DamageWall::~Element_DamageWall()
{
	for (int i = 0; i < 9; i++) {
		if (anim_images[i] != -1) {
			DeleteGraph(anim_images[i]);
			//解放した事を示す為、-1を代入
			anim_images[i] = -1;
		}
	}
}

void Element_DamageWall::Update(Player* player)
{
	//アニメーション更新
	std::function<void()> f = [&]() {
		if (anim_count < 8) { anim_count++; }
		else { anim_count = 0; }
		image = images.at(anim_count);
	};

	LoopTimer(0.1, &f);
	//LoopImages(anim_images, 0.1, 9, nullptr);


	
	if (abs(location.x - player->GetLocation().x) <= MAP_CHIP_SIZE 
		&& abs(location.y - player->GetLocation().y) <= MAP_CHIP_SIZE) {
		ENEMY_TYPE fireType = ENEMY_TYPE::FIRE;
		std::function<void()> Attack = [&]() { player->HpDamage(AttackResource{ 1, &fireType, 5 }); };
		Attack();
		/*if (GetElapsedTime(5.2) == 0.0f) { Attack(); }
		LoopTimer(5.2, &Attack);*/


		//std::function<void()> f = [&]() { player->HpDamage(AttackResource{ 1, nullptr, 5 }); };
		//f();

		//std::function<void()> damage_func = [player]() {
		//	player->HpDamage(AttackResource{ 2, nullptr, 5 });
		//};
	}

}
