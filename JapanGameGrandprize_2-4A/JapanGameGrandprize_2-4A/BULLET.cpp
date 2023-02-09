#include "BULLET.h"
#include "DxLib.h"


BULLET::BULLET()
{
	bullet_x = 0.0;
	bullet_y = 0.0;
	delete_flg = false;
}

BULLET::BULLET(float player_x,float player_y)
{
	delete_flg = false;
	bullet_x = player_x;
	bullet_y = player_y;
}

void BULLET::Draw() const
{
	DrawBox(bullet_x, bullet_y, bullet_x + 20, bullet_y + 20, 0xff00ff, TRUE);
}

void BULLET::Update()
{
	bullet_x += 10;

	if (bullet_x > 1280)
	{
		delete_flg = true;
	}
}

