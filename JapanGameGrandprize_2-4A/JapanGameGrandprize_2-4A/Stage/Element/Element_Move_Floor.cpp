#include "Element_Move_Floor.h"
#include "..//Player.h"

Element_Move_Floor::Element_Move_Floor(short type,
	std::vector<std::shared_ptr<Stage_Element_Base>> element,
	std::vector<int> images, Location location, Area area)
	: Stage_Element_Base(element, &images.at(0), location, { MAP_CHIP_SIZE,MAP_CHIP_SIZE })
{

	this->type = type;
	this->location = location;

	this->area = { MAP_CHIP_SIZE,MAP_CHIP_SIZE - 20 };

	is_move = true;
	speed.x = 5.0f;
	speed.y = 0.0f;

	next_location = { location.x + area.width ,location.y };
}

Element_Move_Floor::~Element_Move_Floor()
{

}

void Element_Move_Floor::Update(Player* player)
{

	Location location = this->GetLocation();
	Location p_location = player->GetLocation();
	HIT_DIRECTION hit_direction = std::get<1>(HitPlayer(player));

    if (location.x == next_location.x) 
	{
        is_move = false;
    }

	//目的位置まで動く
	if (is_move && location.x < next_location.x)
	{
		SetLocation({ location.x + speed.x , location.y + speed.y });
		//目的位置を通り過ぎたら目的位置に戻す
		if (location.x > next_location.x) 
		{
			SetLocation(next_location);
		}
	}

	/*if (hit_direction == HIT_DIRECTION::UP && player->GetState() != PLAYER_STATE::JUMP)
	{
		player->SetLocation({ p_location.x,location.y - MAP_CHIP_SIZE - 5 });
	}*/

	/*if (abs(abs(location.x - p_location.x) <= MAP_CHIP_SIZE
		&& abs(location.y - p_location.y) <= MAP_CHIP_SIZE))
	{
		player->SetLocation({ p_location.x,location.y - MAP_CHIP_SIZE });
	}*/
}

    //if (/*プレイヤーが上に当たっている時*/)
    //{
    //    player->SetLocation({ player->GetLocation().x + speed_x, player->GetLocation().y });
    //}