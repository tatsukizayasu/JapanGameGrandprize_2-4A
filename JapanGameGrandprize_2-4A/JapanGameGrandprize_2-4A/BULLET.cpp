#include "Bullet.h"
#include "DxLib.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Bullet::Bullet()
{
	delete_flg = false;
	efect_explosion = nullptr;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
Bullet::Bullet(float player_x, float player_y)
{
	delete_flg = false;
	efect_explosion = nullptr;
}
