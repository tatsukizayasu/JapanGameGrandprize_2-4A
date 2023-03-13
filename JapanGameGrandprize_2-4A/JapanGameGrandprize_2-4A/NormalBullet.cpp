#include "NormalBullet.h"
#include "CameraWork.h"
#include "Define.h"
#include "player.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
NormalBullet::NormalBullet()
{
	location.x = 0.0;
	location.y = 0.0;
	radius = 4;
	efect_count = 0;
	scrool_x = 0.0;
	scrool_y = 0.0;
	delete_flg = false;
	efect_end = false;

	for (int i = 0; i < 4; i++)
	{
		dot_location_x[i] = 0;
		dot_location_y[i] = 0;
		speed_y[i] = 0;
	}

	speed_x = 0;
}

//-----------------------------------//
// コンストラクタ					 //
//-----------------------------------//
NormalBullet::NormalBullet(float player_x, float player_y,
	                         bool direction,ATTRIBUTE attribute)
{
	delete_flg = false;
	scrool_x = CameraWork::GetCamera().x;
	scrool_y = CameraWork::GetCamera().y;

	location.x = player_x;
	location.y = player_y - 10;
	this->attribute = attribute;
	damage = 10;
	debuff_time = 0;
	this->player_state = player_state;
	player_direction = direction;

	efect_count = 0;
	delete_flg = false;
	efect_end = false;

	for (int i = 0; i < 4; i++)
	{
		dot_location_x[i] = 0;
		dot_location_y[i] = 0;
	}

	speed_x = 1;
	speed_y[0] = 10;
	speed_y[1] = 8;
	speed_y[2] = 6;
	speed_y[3] = 4;
}

//-----------------------------------
// 描画
//-----------------------------------
void NormalBullet::Draw() const
{
	float scrool_x = CameraWork::GetCamera().x;
	float scrool_y = CameraWork::GetCamera().y;

	if (!delete_flg)
	{
		DrawBox(location.x - scrool_x, location.y - scrool_y, (location.x - scrool_x) + 20, (location.y - scrool_y) + 10, 0xff00ff, TRUE);
	}

	if (!efect_end && delete_flg)
	{
		for (int i = 0; i < PIXEL_MAX; i++)
		{
			DrawCircle(dot_location_x[i] - scrool_x, dot_location_y[i] - scrool_y, 2, 0x000000, TRUE);
		}
	}
}

//-----------------------------------
// 更新
//-----------------------------------
void NormalBullet::Update(const Stage* stage_pointa)
{
	float scrool_x = CameraWork::GetCamera().x;
	if (!player_direction)
	{
		if (!HitBlock(stage_pointa) && location.x - scrool_x < 1280 && !delete_flg)
		{
			location.x += 10;
		}
		else
		{
			if (!delete_flg)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					dot_location_x[i] = location.x;
					dot_location_y[i] = location.y;
				}
			}
			delete_flg = true;
		}
	}

	if (player_direction)
	{
		if (!HitBlock(stage_pointa) && location.x - scrool_x > 0 && !delete_flg)
		{
			location.x -= 10;
		}
		else
		{
			if (!delete_flg)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					dot_location_x[i] = location.x;
					dot_location_y[i] = location.y;
				}
			}
			delete_flg = true;
		}
	}

	if (delete_flg)
	{
		NormalBulletEfect();
	}
}

bool NormalBullet::NormalBulletEfect()
{
	if (!efect_end)
	{
		if (++efect_count % 30 != 0)
		{
			for (int i = 0; i < PIXEL_MAX; i++)
			{
				if (player_direction)
				{
					dot_location_x[i] += speed_x;
					dot_location_y[i] += speed_y[i];
				}
				else
				{
					dot_location_x[i] -= speed_x;
					dot_location_y[i] += speed_y[i];
				}
			}
		}
		else
		{
			if (player_direction)
			{
				location.x--;
				location.y--;
				efect_end = true;
				return true;
			}
			else
			{
				location.x++;
				location.y++;
				efect_end = true;
				return true;
			}
		}
	}
	return false;
}