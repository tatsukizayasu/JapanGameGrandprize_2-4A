#include "Element_DamageWall.h"
#include "../Player.h"


Element_DamageWall::Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : Stage_Element_Base(element, image, location, area)
{
	this->type = type;
	LoadDivGraph("Images/Stage/Element/DamageWall.png", 9, 9, 1, 40, 40, anim_images);
	image = &anim_images[0];
	anim_count = 0;
}

Element_DamageWall::~Element_DamageWall()
{
}

void Element_DamageWall::Update(Player* player)
{
	//アニメーション更新
	std::function<void()> f = [&]() {
		if (anim_count < 8) { anim_count++; }
		else { anim_count = 0; }
		image = anim_images[anim_count];
	};

	StartAnimation(0.1, &f);


	
	if (abs(location.x - player->GetLocation().x) <= MAP_CHIP_SIZE 
		&& abs(location.y - player->GetLocation().y) <= MAP_CHIP_SIZE) {
		std::function<void()> Attack = [&]() { player->HpDamage(AttackResource{ 1, nullptr, 5 }); };
		Attack();
	}
	
	if (HitPlayer(player))
	{
		//printfDx("当たってるよ\n");		
		//std::function<void()> f = [&]() { player->HpDamage(AttackResource{ 1, nullptr, 5 }); };
		//f();
		//StartAnimation(10.2, [&]() {player->HpDamage(AttackResource{1, nullptr, 5});});
		//StartAnimation(3.2, &f);
		//if (GetAnimationTime() < 5.1) { image = 0; }
	}

}

void Element_DamageWall::Damage(Player *player)
{
	player->HpDamage(AttackResource{ 1, nullptr, 5 });
}



//void Element_DamageWall::Draw() const
//{
//
//}
