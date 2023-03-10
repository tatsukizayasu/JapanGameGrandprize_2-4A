#include "Element_DamageWall.h"
#include "../Player.h"

Element_DamageWall::Element_DamageWall(MapChip* mapchip, int image) : Stage_Element_Base(mapchip, image)
{
}

Element_DamageWall::~Element_DamageWall()
{
}

void Element_DamageWall::Update(Player* player)
{
	if (HitPlayer(player))
	{
		//printfDx("“–‚½‚Á‚Ä‚é‚æ\n");		
		player->HpDamage(AttackResource{ 1, nullptr, 5 });
	}
}

void Element_DamageWall::Draw() const
{
}