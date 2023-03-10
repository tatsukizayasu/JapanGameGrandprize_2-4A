#include "Stage_Element.h"

Stage_Element::Stage_Element()
{
	player = nullptr;
}

Stage_Element::~Stage_Element()
{
}

void Stage_Element::AddElement(short type, int* image, Location location, Area area)
{

	switch (type)
	{
	case Element::GreenButton:
		element.push_back(std::make_shared<Element_DamageWall>(type, element, image, location, area));
		break;

	case Element::DEBUG_GRASS:
		element.push_back(std::make_shared <Element_Wooden_Floor>(type, element, image, location, area));
		break;

	case Element::YellowButton:
		element.push_back(std::make_shared <Element_Wooden_Floor>(type, element, image, location, area));
		break;

	default:
		break;
	}
	
}

void Stage_Element::Update(Player* player)
{
	for (auto& e : element)
	{
		e->MapChip::Update(player);
	}
}

void Stage_Element::Draw() const
{
	for (auto& e : element)
	{
		e->MapChip::Draw();
	}
}