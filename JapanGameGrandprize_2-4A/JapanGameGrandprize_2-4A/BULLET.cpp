#include "Bullet.h"
#include "DxLib.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Bullet::Bullet()
{
	efect_end = false;
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

bool Bullet::GetEfectFlg()
{
	return efect_end;
}
