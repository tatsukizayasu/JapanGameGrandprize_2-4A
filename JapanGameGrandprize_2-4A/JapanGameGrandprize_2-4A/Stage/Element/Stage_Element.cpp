#include "Stage_Element.h"

Stage_Element::Stage_Element()
{
	player = nullptr;
}

Stage_Element::~Stage_Element()
{
}

void Stage_Element::AddElement(MapChip* mapchip, int image , short id)
{
		switch (id)
		{
		case Element::DEBUG_WOOD:
			element.push_back(new Element_DamageWall(mapchip, image));
			break;

		case Element::DEBUG_GRASS:
			element.push_back(new Element_Wooden_Floor(mapchip, image));
			break;

		case Element::DEBUG_SOIL:
			element.push_back(new Element_Wooden_Floor(mapchip, image));
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