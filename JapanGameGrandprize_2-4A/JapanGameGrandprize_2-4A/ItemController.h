#pragma once
#include"Item.h"

class ItemController
{
private:
	int item_volume; //生成しているアイテムの量

	Item** item; //アイテム
public:

	//コンストラクタ
	ItemController();

	//デストラクタ
	~ItemController();
	//アイテムの生成
	void SpawnItem();

	//アイテムの並び替え
	void SortItem();
};