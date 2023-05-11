#include "Element_DamageWall.h"
#include "../Player.h"

Element_DamageWall::Element_DamageWall(short type, Resource resource, Location location, Area area) : Stage_Element_Base(&resource.images.at(0), location, area)
{

	this->area = area;
	this->type = type;
	
	this->resource = resource;
	this->images = resource.images;
}

Element_DamageWall::~Element_DamageWall() = default;

void Element_DamageWall::Update(Player* player)
{
	
	if (CheckSoundMem(resource.sounds.at(0)) == FALSE) {
		SetPan(resource.sounds.at(0), player, this);
		PlaySoundMem(resource.sounds.at(0), DX_PLAYTYPE_BACK, TRUE);
	}

	//アニメーション更新
	LoopImages(images, 0.1f, 9, nullptr);

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