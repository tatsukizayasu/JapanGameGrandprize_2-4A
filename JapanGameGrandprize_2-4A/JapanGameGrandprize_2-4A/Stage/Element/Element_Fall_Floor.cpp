#include "Element_Fall_Floor.h"
#include "../Player.h"


Element_Fall_Floor::Element_Fall_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->area = area;
	this->type = type;
	margin_area = { -18.0f,0.0f };
	this->images = images;

	
	is_flash = false;
	fall_speed = 5.0f;
	
}

Element_Fall_Floor::~Element_Fall_Floor()
{
	for (int i = 0; i < 9; i++) {
		if (anim_images[i] != -1) {
			DeleteGraph(anim_images[i]);
			//解放した事を示す為、-1を代入
			anim_images[i] = -1;
		}
	}
}

void Element_Fall_Floor::Update(Player* player)
{

	//LoopImages(anim_images, 0.1, 9, nullptr);

	HIT_DIRECTION is_hit_dir = std::get<1>(HitPlayer(player));

	if (is_hit_dir == HIT_DIRECTION::UP && state != STATE::FALL) {
		//アニメーション更新
		std::function<void()> flash = [&]() {
			is_flash = !is_flash;

			//state = STATE::FLASH;

			if (is_flash) {
				SetImage(0);
			}
			else {
				SetImage(images.at(0));
			}
			
		};

		if (state == STATE::WORKING) { LoopTimer(0.3f, &flash); };


		if (GetElapsedTime(4.0f) >= 2.0f) { state = STATE::WORKING; }

		std::function<void()> fall = [&]() {

			state = STATE::FALL;
			
		};

		LoopTimer(4.0f, &fall);
		
	}
	//else {
	//	state = STATE::NONE;
	//}

	if (state == STATE::FALL) {
		if (GetLocation().y < 2000) {
			SetLocation({ GetLocation().x, GetLocation().y + fall_speed });
		}
		
	}

}
