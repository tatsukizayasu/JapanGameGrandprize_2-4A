#pragma once
#include "SphereCollider.h"
#include "EnumElementItem.h"
class Item :
	public SphereCollider
{
private:
	int color; //色
public:
	//コンストラクタ
	Item();
	Item(ELEMENT_ITEM type, Location location);

	//更新
	void Update();

	//描画
	void Draw()const;
};

