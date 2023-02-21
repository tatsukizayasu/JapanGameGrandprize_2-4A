#include "Bullet.h"
#include "DxLib.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
BulletBase::BulletBase()
{
	efect_end = false;
	delete_flg = false;
	efect_explosion = nullptr;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
BulletBase::BulletBase(float player_x, float player_y)
{
	delete_flg = false;
	efect_explosion = nullptr;
}

bool BulletBase::GetEfectFlg()
{
	return efect_end;
}

float BulletBase::GetDamage()
{
	return damage;
}

float BulletBase::GetDebuffTime()
{
	return debuff_time;
}

ATTRIBUTE BulletBase::GetAttribute()
{
	return attribute;
}