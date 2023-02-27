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

	//更新
	void Update( class Player* player);

	//描画
	void Draw() const;

	//アイテムの生成
	void SpawnItem(const class EnemyBase* enemy);

	//アイテムの並び替え
	void SortItem(const int item_num);

	//アイテムの整理
	void ArrangementItem(const int old_item_volume);

};