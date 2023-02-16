#include "NormalBullet.h"
#include "CameraWork.h"
#include "Define.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
NormalBullet::NormalBullet()
{
	location.x = 0.0;
	location.y = 0.0;
	efect_count = 0;
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
NormalBullet::NormalBullet(float player_x, float player_y)
{
	delete_flg = false;
	location.x = player_x;
	location.y = player_y;

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
	if (!delete_flg)
	{
		DrawBox(location.x, location.y, location.x + 20, location.y + 10, 0xff00ff, TRUE);
	}
	if (!efect_end && delete_flg)
	{
		for (int i = 0; i < PIXEL_MAX; i++)
		{
			DrawCircle(dot_location_x[i], dot_location_y[i], 2, 0x000000, TRUE);
		}
	}
}

//-----------------------------------
// 更新
//-----------------------------------
void NormalBullet::Update()
{
	if (location.x - CameraWork::GetCamera().x < 1260 && !delete_flg)
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
				dot_location_x[i] -= speed_x;
				dot_location_y[i] += speed_y[i];
			}
		}
		else
		{
			location.x++;
			location.y++;
			efect_end = true;
			return true;
		}
	}
	return false;
}
