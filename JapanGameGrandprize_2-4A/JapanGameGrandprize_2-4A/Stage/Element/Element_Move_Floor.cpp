#include "Element_Move_Floor.h"
#include "..//Player.h"

Element_Move_Floor::Element_Move_Floor(short type,
	std::vector<int> images, Location location, Area area)
	: Stage_Element_Base(&images.at(0), location, { MAP_CHIP_SIZE,MAP_CHIP_SIZE })
{
	this->type = type;
	this->location = location;
	this->area = { MAP_CHIP_SIZE - 20,MAP_CHIP_SIZE };
	margin_area = { 0.0f,0.0f };

	is_move = false;
	speed.x = 5.0f;
	speed.y = 0.0f;
	next_location = { 0.0f,0.0f };
	move_timer = 0;
	is_goal_object = false;
}

Element_Move_Floor::Element_Move_Floor(short type, Location location)
{
	this->type = type;
	this->location = location;
	this->area = { -MAP_CHIP_SIZE,-MAP_CHIP_SIZE };
	margin_area = { 0.0f,0.0f };
	is_move = false;
	speed = { 0.0f,0.0f };
	next_location = { 0.0f,0.0f };
	move_timer = 0;
	is_goal_object = true;
}

Element_Move_Floor::~Element_Move_Floor()
{

}

void Element_Move_Floor::Update(Player* player)
{
	
	if (is_goal_object == false)
	{
		Location location = this->GetLocation();
		Location p_location = player->GetLocation();
		HIT_DIRECTION hit_direction = std::get<1>(HitPlayer(player));

		if (hit_direction == HIT_DIRECTION::UP)
		{
			if (MOVE_START_TIME <= move_timer++)
			{
				is_move = true;
			}
		}

		if (location.x == next_location.x)
		{
			is_move = false;
			move_timer = 0;
		}

		//動く条件である場合
		if (is_move)
		{
			//目的位置まで動く
			if (location.x != next_location.x)
			{
				this->location.x += speed.x;
				this->location.y += speed.y;

				//目的位置を通り過ぎたら目的位置に戻す
				if (next_location.x < location.x)
				{
					this->location.x = next_location.x;
				}
			}
			//プレイヤーが乗っているとき、プレイヤー座標に床のスピードを加算する
			if (hit_direction == HIT_DIRECTION::UP && player->GetState() != PLAYER_STATE::JUMP && player->GetState() != PLAYER_STATE::FLY)
			{
				player->SetLocation({ p_location.x + speed.x,p_location.y + speed.y });
			}

		}
	}
}

void Element_Move_Floor::SetLocation(Location location)
{
	next_location = location;
}
