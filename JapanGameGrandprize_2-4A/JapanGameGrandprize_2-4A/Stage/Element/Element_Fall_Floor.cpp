#include "Element_Fall_Floor.h"
#include "../Player.h"
#include "../CameraWork.h"

#define TIMER	1.8f

Element_Fall_Floor::Element_Fall_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element,
	std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{

	this->area = area;
	this->type = type;
	margin_area = { -12.0f,0.0f };
	this->images = images;

	is_flash = false;
	fall_speed = 4.0f;
	increment = 0.1f;
	
	state = STATE::NONE;
}

Element_Fall_Floor::~Element_Fall_Floor()
{

	for (int& image : images) 
	{
		DeleteGraph(image);
	}
}

void Element_Fall_Floor::Update(Player* player)
{

	//LoopImages(anim_images, 0.1, 9, nullptr);

	HIT_DIRECTION is_hit_dir = std::get<1>(HitPlayer(player));

	if (state != STATE::FALL) 
	{
		if (is_hit_dir == HIT_DIRECTION::UP)
		{
			//アニメーション更新
			std::function<void()> flash = [&]()
			{
				is_flash = !is_flash;

				if (is_flash) 
				{
					SetImage(0);
				}
				else 
				{
					SetImage(images.at(0));
				}
			};

			//点滅するタイマーをセット
			if (state == STATE::WORKING) { LoopTimer(0.3f, &flash); };

			//落ちる時間の半分の時間が経過したらステートをWORKING!!にセットし、点滅させる
			if (GetElapsedTime(TIMER) >= 0.01f) { state = STATE::WORKING; }

			std::function<void()> fall = [&]() 
			{
				state = STATE::FALL;
			};

			//落ちる時間のタイマーをセット
			LoopTimer(TIMER, &fall);
		}
		else 
		{
			state = STATE::NONE;
			SetImage(images.at(0));
			ResetElapsedTime(TIMER);
		}
	}

	if (state == STATE::FALL)
	{
		SetImage(images.at(0));

		if (GetLocation().y < CameraWork::GetCamera().y + static_cast<float>(SCREEN_HEIGHT) + MAP_CHIP_SIZE) 
		{
			fall_speed += increment;
			SetLocation({ GetLocation().x, GetLocation().y + fall_speed });
		}
	}
}