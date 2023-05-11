#pragma once
#include "Stage_Element_Base.h"
#include "../ItemController.h"
#include "../ElementItem.h"

class Element_Item_Drop_Object : public Stage_Element_Base
{
private:

	enum class STATE {
		NONE,		//Ç»Çµ
		DESTROY,	//îjâÛ
		EXTINGUISHMENT	//è¡ñ≈
	}state;

	ItemController* item_con;
	std::vector<ElementItem> element_item;
	int drop_volume;

public:

	Element_Item_Drop_Object(short type, Resource resource, Location location, Area area);
	~Element_Item_Drop_Object();
	void Update(Player* player)override;
	void Draw()const override;
};