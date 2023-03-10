#include "Stage_Element_Base.h"
#include "../MapChip.h"
#include "../Player.h"
#include <windef.h>

Stage_Element_Base::Stage_Element_Base()
{
	this->mapchip = nullptr;
	this->image = 0;
	type = 0;
}

Stage_Element_Base::Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : MapChip(image, location, area)
{
	this->mapchip = mapchip;
}

Stage_Element_Base::~Stage_Element_Base()
{
}

bool Stage_Element_Base::HitPlayer(Player* player) const
{
	

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


//std::shared_ptr<Stage_Element_Base> Stage_Element_Base::SearchElement(short type)
//{
//	for (auto elem : element) {
//		if (elem != nullptr && elem->GetType() == type) {
//			//MapChip* mapchip = elem->GetMapChip();
//
//			if (mapchip->GetLocation().y > elem->GetMapChip()->GetLocation().y
//				&& mapchip->GetLocation().x == elem->GetMapChip()->GetLocation().x) {
//
//				SearchElement(type)->GetMapChip()->SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
//				SearchElement(type)->GetMapChip()->SetImage(0);
//				printfDx("aa");
//				return elem;
//			}
//			
//		}
//	}
//}