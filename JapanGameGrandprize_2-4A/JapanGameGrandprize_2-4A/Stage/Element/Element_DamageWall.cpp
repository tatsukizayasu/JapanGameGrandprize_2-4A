#include "Element_DamageWall.h"
#include "../Player.h"
#include "Stage_Element.h"


Element_DamageWall::Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, MapChip* mapchip, int image) : Stage_Element_Base(element, mapchip, image)
{
	this->type = Element::DEBUG_WOOD;
}

Element_DamageWall::~Element_DamageWall()
{

}

void Element_DamageWall::Update(Player* player)
{
	if (HitPlayer(player)) {
		//printfDx("“–‚½‚Á‚Ä‚é‚æ\n");		
		player->HpDamage(AttackResource{ 1, nullptr, 5 });
		mapchip->SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
		mapchip->SetImage(0);
	}
}

void Element_DamageWall::Draw() const
{
	
}
