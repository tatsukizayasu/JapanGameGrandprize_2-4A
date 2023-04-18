#include "Element_Wooden_Floor.h"
#include "../Player.h"
#include "../PadInput.h"
#include "Stage_Element.h"
#include "../CameraWork.h"

Element_Wooden_Floor::Element_Wooden_Floor(short type, 
	std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, 
	Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{

	this->type = type;
	this->location = location;
	this->area = area;

	margin_area = { -12.0f,0.0f };

	original_collision = area;

	SetImage(images.at(0));
	original_image = images.at(0);
}

Element_Wooden_Floor::~Element_Wooden_Floor()
{

}

void Element_Wooden_Floor::Update(Player* player)
{

	bool is_hit = std::get<0>(HitPlayer(player));
	HIT_DIRECTION is_hit_dir = std::get<1>(HitPlayer(player));

	// プレイヤーが下にいる&ステートがジャンプの場合
	if (is_hit && is_hit_dir == HIT_DIRECTION::DOWN)
	{
		if (player->GetState() == PLAYER_STATE::FLY)
		{
			SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
		}
		else 
		{
			SetArea(original_collision);
		}
	}
	// プレイヤーが上にいる&左スティックを下に倒した場合
	else if (is_hit && is_hit_dir == HIT_DIRECTION::UP
		&& player->GetLocation().y + player->GetArea().height / 2 < location.y + margin_area.height
		&& PAD_INPUT::GetLStick().y <= -10000)
	{
		SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
	}
	// プレイヤーが接触していない状態で、一定距離離れると衝突エリアをリセット
	else if (abs(location.y - player->GetLocation().y) >= MAP_CHIP_SIZE - margin_area.height + 8.0f) 
	{
		SetArea(original_collision);
	}

	//if (is_hit == true) {
	//	//SetArea(original_collision);
	//	static int count = 0;
	//	printfDx("当たり～ %d回目\n", count);
	//	count++;
	//}
}