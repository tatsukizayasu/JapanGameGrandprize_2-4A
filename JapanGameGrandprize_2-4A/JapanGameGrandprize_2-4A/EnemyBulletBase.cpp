#include "EnemyBulletBase.h"


//-----------------------------------
//ダメージの取得
//-----------------------------------
int EnemyBulletBase::GetDamage() const
{
	return damage;
}

//-----------------------------------
//タイプの取得
//-----------------------------------
ENEMY_TYPE EnemyBulletBase::GetType() const
{
	return type;
}