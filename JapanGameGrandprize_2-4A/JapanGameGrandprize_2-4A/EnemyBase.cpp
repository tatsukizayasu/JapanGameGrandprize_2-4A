#include "DxLib.h"
#include "EnemyBase.h"


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
//アイテムの生成
//-----------------------------------
void EnemyBase::CreateDropItem(int drop_num,Location location)
{
	int volume = 0; //生成数
	int j = 0;
	for (int i = 0; i < drop_num; i++)
	{
		volume = drop_element[i]->GetVolume();
		while (0 < volume)
		{
			drop_item[j++] = new Item(drop_element[i]->GetType(), location);
			volume--;
		}
	}
}

//-----------------------------------
//アイテムの並び替え
//-----------------------------------
void EnemyBase::SortDropitem(int item_num)
{
	//弾の中身をソートする
	for (int i = item_num + 1; i < drop_volume; i++)
	{
		if ((drop_item[i] == nullptr))
		{
			break;
		}
		drop_item[i - 1] = drop_item[i];
		drop_item[i] = nullptr;
	}
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

