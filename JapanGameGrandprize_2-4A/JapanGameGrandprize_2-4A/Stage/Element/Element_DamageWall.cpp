#include "Element_DamageWall.h"
#include "../Player.h"


Element_DamageWall::Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : Stage_Element_Base(element, image, location, area)
{
	this->type = type;
}

Element_DamageWall::~Element_DamageWall()
{
}

void Element_DamageWall::Update(Player* player)
{
	
	if (HitPlayer(player))
	{
		//printfDx("“–‚½‚Á‚Ä‚é‚æ\n");		
		std::function<void()> f = [&]() { player->HpDamage(AttackResource{ 1, nullptr, 5 }); };
		//StartAnimation(10.2, [&]() {player->HpDamage(AttackResource{1, nullptr, 5});});
		StartAnimation(10.2, &f);
		if (GetAnimationTime() < 5.1) { image = 0; }
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
