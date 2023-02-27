#pragma once
#include "EnumElementItem.h"

class ElementItem
{
private:

	unsigned int volume; //量
	ELEMENT_ITEM type; //元素タイプ
public:

	//コンストラクタ
	ElementItem();
	ElementItem(ELEMENT_ITEM type);

	//元素の量を取得
	unsigned int GetVolume()const;

	//元素タイプの取得
	ELEMENT_ITEM GetType() const;

	//元素の量を設定
	void SetVolume(unsigned int num);
};