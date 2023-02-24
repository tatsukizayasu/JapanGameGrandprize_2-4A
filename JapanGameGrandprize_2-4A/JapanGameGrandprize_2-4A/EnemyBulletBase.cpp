#include "EnemyBulletBase.h"
#include "Define.h"
#include "CameraWork.h"


//-----------------------------------
//画面外に出たかどうか
//-----------------------------------
bool EnemyBulletBase::ScreenOut()
{
	bool ret = false; //戻り値
	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	if ((x < 0) || (SCREEN_WIDTH < x) || (y < 0) || (SCREEN_HEIGHT < y))
	{
		ret = true;
	}

	return ret;
}

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