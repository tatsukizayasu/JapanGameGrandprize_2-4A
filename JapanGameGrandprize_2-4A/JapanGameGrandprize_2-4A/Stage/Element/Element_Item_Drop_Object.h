#pragma once
#include "Stage_Element_Base.h"
#include "../ItemController.h"
#include "../ElementItem.h"

class Element_Item_Drop_Object : public Stage_Element_Base
{
private:

	enum class STATE {
		NONE,		//‚È‚µ
		DESTROY,	//”j‰ó
	}state;

	ItemController* item_con;
	std::vector<ElementItem> element_item;

public:

	Element_Item_Drop_Object(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	~Element_Item_Drop_Object();
	void Update(Player* player)override;
	void Draw()const override;
};