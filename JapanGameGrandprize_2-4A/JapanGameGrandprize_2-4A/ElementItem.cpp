#include "ElementItem.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
ElementItem::ElementItem()
{

	volume = 0;
	type = ELEMENT_ITEM::NONE;
}

//-----------------------------------
//コンストラクタ
//-----------------------------------
ElementItem::ElementItem(ELEMENT_ITEM type)
{

	volume = 0;
	this->type = type;
}

//-----------------------------------
//元素の量を取得
//-----------------------------------
unsigned int ElementItem::GetVolume()const
{

	return volume;
}

//-----------------------------------
//元素タイプの取得
//-----------------------------------
ELEMENT_ITEM ElementItem::GetType() const
{

	return type; 
}

//-----------------------------------
//元素の量を設定
//-----------------------------------
void ElementItem::SetVolume(unsigned int num)
{

	volume = num;
}