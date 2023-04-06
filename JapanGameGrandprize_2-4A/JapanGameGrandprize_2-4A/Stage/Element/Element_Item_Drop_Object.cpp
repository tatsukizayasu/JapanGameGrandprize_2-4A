#include "Element_Item_Drop_Object.h"

Element_Item_Drop_Object::Element_Item_Drop_Object(short type,
	std::vector<std::shared_ptr<Stage_Element_Base>> element,
	std::vector<int> images, Location location, Area area)
	: Stage_Element_Base(element, &images.at(0), location, area)
{

}

Element_Item_Drop_Object::~Element_Item_Drop_Object()
{

}
