#pragma once
#include "Stage_Element_Base.h"

class Element_Item_Drop_Object : public Stage_Element_Base
{
private:

public:
	Element_Item_Drop_Object(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	~Element_Item_Drop_Object();
};