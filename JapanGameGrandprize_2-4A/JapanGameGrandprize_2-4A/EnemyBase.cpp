#include "DxLib.h"
#include "EnemyBase.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
EnemyBase::EnemyBase() 
{
	hp = 0;
	speed = 0;
	drop_volume = 0;
	drop_type_volume = 0; 

	drop_element = nullptr;

	kind = ENEMY_KIND::NONE; 
	type = nullptr;
}
//-----------------------------------
// HPが0かどうか判断(0になったらtrue)
//-----------------------------------
bool EnemyBase::CheckHp()
{
	bool ret = false;
	if (hp <= 0)
	{
		ret = true;
	}
	return ret;
}

//-----------------------------------
//ドロップする種類の量の取得
//-----------------------------------
int EnemyBase::GetDropTypeVolume() const
{
	return drop_type_volume;
}

//-----------------------------------
//ドロップするアイテムの量の取得
//-----------------------------------
int EnemyBase::GetDropVolume()const
{
	return drop_volume;
}

//-----------------------------------
// ドロップアイテムの取得
//-----------------------------------
ElementItem EnemyBase::GetDropItem(int i) const
{ 
	return *drop_element[i]; 
}

//-----------------------------------
// エネミーの種類の取得
//-----------------------------------
ENEMY_KIND EnemyBase::GetEnemyKind() const
{
	return kind;
}

//-----------------------------------
//削除可能状態の取得
//-----------------------------------
bool EnemyBase::GetCanDelete() const
{
	return can_delete;
}