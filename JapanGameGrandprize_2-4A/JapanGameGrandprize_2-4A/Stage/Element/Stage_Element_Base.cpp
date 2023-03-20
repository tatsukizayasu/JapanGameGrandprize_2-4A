#include "Stage_Element_Base.h"
#include "../MapChip.h"
#include "../Player.h"
#include <windef.h>


Stage_Element_Base::Stage_Element_Base()
{
	type = 0;
	this->mapchip = nullptr;
	this->image = 0;
	type = 0;
	count = 0;

}

Stage_Element_Base::Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : MapChip(image, location, area)
{
	type = 0;
	this->mapchip = mapchip;
	start_time = chrono::steady_clock::now();
	std::chrono::duration<float> diff = chrono::steady_clock::now() - start_time;
	elapsed = chrono::duration_cast<chrono::duration<long long, std::milli>>(diff);
	count = 0;
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

void Stage_Element_Base::StartAnimation(float time, std::function<void()>* callback)
{
	auto end_time = chrono::steady_clock::now();
	auto diff = end_time - start_time;
	//elapsed = chrono::duration_cast<chrono::milliseconds>(diff);
	elapsed = chrono::duration_cast<chrono::duration<long long, std::milli>>(diff);

	if (elapsed.count() >= time * 1000.0f) {
		start_time = end_time;
		count++;
		//printfDx("count:%d\n", count);

		if (callback != nullptr) {
			(*callback)();
		}

	}

}

void Stage_Element_Base::LoopImages(int *images, float time, int total_images, std::function<void()>* callback)
{
	

	auto end_time = std::chrono::steady_clock::now();
	auto diff = end_time - start_time;
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

	if (elapsed.count() >= time * 1000.0f) {
		start_time = end_time;
		current_image = (current_image + 1) % total_images;
		this->image = images[current_image];

		if (callback != nullptr) {
			(*callback)();
		}

	}
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

