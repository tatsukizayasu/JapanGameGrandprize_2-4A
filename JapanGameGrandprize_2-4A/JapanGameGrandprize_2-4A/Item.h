#pragma once
#include "SphereCollider.h"
#include "EnumElementItem.h"
#include "Player.h"

class Item :
	public SphereCollider
{
private:

	int color; //色
	int speed; //速度
	ELEMENT_ITEM element_type; //元素
public:

	//コンストラクタ
	Item();
	Item(ELEMENT_ITEM type, Location location);

	//更新
	void Update(Player* player);

	//描画
	void Draw()const;

	//元素のタイプの取得
	ELEMENT_ITEM GetElementType() const;
};