#include "Stage_Element.h"


Stage_Element::Stage_Element()
{
	player = nullptr;
}


Stage_Element::~Stage_Element()
{
	element.clear();
	element.shrink_to_fit();
	delete player;
}

void Stage_Element::AddElement(MapChip* mapchip, int image, short id)
{

	switch (id)
	{
	case Element::DEBUG_WOOD:
		element.push_back(std::make_shared<Element_DamageWall>(id, element, mapchip, image));
		break;

	case Element::DEBUG_GRASS:
		element.push_back(std::make_shared <Element_Wooden_Floor>(id, element, mapchip, image));
		break;

	case Element::DEBUG_SOIL:
		element.push_back(std::make_shared <Element_Wooden_Floor>(id, element, mapchip, image));
		break;

	default:
		break;
	}

}

void Stage_Element::Update(Player* player)
{
	for (auto& e : element)
	{
		e->Update(player);
	}

}


void Stage_Element::Draw() const
{
	for (auto& e : element)
	{
		e->Draw();
	}
}
