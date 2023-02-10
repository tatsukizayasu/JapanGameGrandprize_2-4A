#include "BULLET.h"
#include "DxLib.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
BULLET::BULLET()
{
	bullet_x = 0.0;
	bullet_y = 0.0;
	delete_flg = false;
	efect_explosion = nullptr;
	type = BULLET_TYPE::NORMAL;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
BULLET::BULLET(float player_x, float player_y,BULLET_TYPE bullet_type)
{
	delete_flg = false;
	bullet_x = player_x;
	bullet_y = player_y;
	efect_explosion = nullptr;
	type = bullet_type;	
}

//-----------------------------------
// 描画
//-----------------------------------
void BULLET::Draw() const
{
	switch (type)
	{
	case BULLET_TYPE::NORMAL:
		break;
	case BULLET_TYPE::EXPLOSION:
		efect_explosion->Draw();
		break;
	case BULLET_TYPE::MELT:
		break;
	case BULLET_TYPE::WARTER:
		break;
	case BULLET_TYPE::POISON:
		break;
	case BULLET_TYPE::PARALYSIS:
		break;
	case BULLET_TYPE::FROZEN:
		break;
	case BULLET_TYPE::SPECIAL:
		break;
	default:
		break;
	}
}

//-----------------------------------
// 更新
//-----------------------------------
void BULLET::Update()
{
	if (bullet_x < 1280)
	{
		bullet_x += 10;
	}
	else
	{
		delete_flg = 0;
	}
}