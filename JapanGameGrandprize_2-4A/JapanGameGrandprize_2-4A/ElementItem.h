#pragma once

//元素構造体
enum class  ELEMENT_ITEM
{
	OXYGEN,      //酸素
	HYDROGEN,	 //水素
	NITROGEN,	 //窒素
	CARBON,		 //炭素
	SULFUR,		 //硫黄
	CHLORINE,	 //塩素
	URANIUM,	 //ウラン
	NONE
};

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
};

