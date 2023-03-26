#include "ItemController.h"
#include "EnemyBase.h"
#include "Player.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
ItemController::ItemController()
{
	item_volume = 0;
	item_max = 0;
	item = nullptr;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
ItemController::~ItemController()
{
	for (int i = 0; i < item_volume; i++)
	{
		delete item[i];
	}

	delete[] item;
}

//-----------------------------------
//更新
//-----------------------------------
void ItemController::Update(Player* player)
{
	for (int i = 0; i < item_volume; i++)
	{
		if (item[i] == nullptr)
		{
			break;
		}

		item[i]->Update(player->GetLocation());

		if (item[i]->HitBox(player))
		{
			player->SetElementItem(item[i]);
			delete item[i];
			item[i] = nullptr;
			SortItem(i);
			i--;
			item_volume--;
		}
	}
}

//-----------------------------------
//アイテムの生成
//-----------------------------------
void ItemController::SpawnItem(const EnemyBase* enemy_base)
{

	int old_item_max = item_max;//生成可能なエネミー数

	item_volume += enemy_base->GetDropVolume();

	if (item_max < item_volume)
	{
		item_max = item_volume;
		ArrangementItem(old_item_max);
	}

	int volume = 0; //生成数
	int j = 0;

	//アイテムの生成
	for (int i = 0; i < enemy_base->GetDropTypeVolume(); i++)
	{
		volume = enemy_base->GetDropItem(i).GetVolume();

		for (int j = 0; j < volume; j++)
		{
			for (int n = 0; n < item_max; n++)
			{
				if (item[n] == nullptr)
				{
					item[n] = new Item(enemy_base->GetDropItem(i).GetType(),
						                enemy_base->GetLocation());
					break;
				}
			}
		}
	}
}

//-----------------------------------
//アイテムの並び替え
//-----------------------------------
void ItemController::SortItem(const int item_num)
{
	//弾の中身をソートする
	for (int i = item_num + 1; i < item_max; i++)
	{
		if ((item[i] == nullptr))
		{
			break;
		}

		item[i - 1] = item[i];
		item[i] = nullptr;
	}
}

//-----------------------------------
//アイテムの整理
//-----------------------------------
void ItemController::ArrangementItem(const int old_item_max)
{
	if (item == nullptr)
	{
		//アイテムの初期化
		item = new Item * [item_max];

		for (int i = 0; i < item_max; i++)
		{
			item[i] = nullptr;
		}
	}
	else
	{
		Item** temporary_item; //避難用

		//もともとのアイテム一時的に避難する
		temporary_item = item;

		item = new Item * [item_max];

		//避難させたアイテムを元に戻す
		item = temporary_item;

		for (int i = old_item_max; i < item_max; i++)
		{
			item[i] = nullptr;
		}

	}

}

//-----------------------------------
//描画
//-----------------------------------
void ItemController::Draw() const
{
	for (int i = 0; i < item_volume; i++)
	{
		if (item[i] == nullptr)
		{
			break;
		}

		item[i]->Draw();
	}
}