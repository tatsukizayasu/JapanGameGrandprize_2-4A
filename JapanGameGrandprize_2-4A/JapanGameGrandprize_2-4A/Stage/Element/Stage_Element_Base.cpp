#include "Stage_Element_Base.h"
#include "../MapChip.h"
#include "../Player.h"
#include <windef.h>

Stage_Element_Base::Stage_Element_Base()
{
	this->mapchip = nullptr;
	this->image = nullptr;
}

Stage_Element_Base::Stage_Element_Base(MapChip* mapchip, int* image)
{
	this->mapchip = mapchip;
	this->image = image;
}

Stage_Element_Base::~Stage_Element_Base()
{
}


bool Stage_Element_Base::HitPlayer(Player* player) const
{
	Location location = mapchip->GetLocation();
	Area area = mapchip->GetArea();

	struct Rect
	{
		float x;
		float y;
		float height;
		float width;
	};

	//ï‚ê≥


	Rect mapchip_rect = { location.x - (area.width / 2), location.y - (area.height / 2), area.height, area.width };


	Location p_location = player->GetLocation();
	Area p_area = player->GetArea();

	//ï‚ê≥
	const float x = 1.0f;
	const float y = 1.0f;

	Rect player_rect = { p_location.x - (p_area.width / 2), p_location.y - (p_area.height / 2), p_area.height, p_area.width };



	if ((mapchip_rect.x - x < player_rect.x + player_rect.width) && (player_rect.x < mapchip_rect.x + mapchip_rect.width + x)
		&& (mapchip_rect.y - y < player_rect.y + player_rect.height) && (player_rect.y < mapchip_rect.y + mapchip_rect.height + y))
	{
		return true;
	}
	return false;
}
