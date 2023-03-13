#include "Stage_Element.h"
#include "../CameraWork.h"

//#define NODEBUG

Stage_Element::Stage_Element()
{
	player = nullptr;
}

Stage_Element::~Stage_Element()
{
}

void Stage_Element::AddElement(short type, int* image, Location location, Area area)
{
#ifndef NODEBUG



	switch (type)
	{
	case Element::DEBUG_WOOD:
		element.push_back(std::make_shared<Element_DamageWall>(type, element, image, location, area));
		break;

	case Element::DEBUG_GRASS:
		element.push_back(std::make_shared <Element_Wooden_Floor>(type, element, image, Location{location.x, location.y}, Area{ 10.0f, MAP_CHIP_SIZE }));
		break;

	case Element::DEBUG_SOIL:
		element.push_back(std::make_shared <Element_Wooden_Floor>(type, element, image, location, Area{ 10.0f, MAP_CHIP_SIZE }));
		break;

	default:
		break;
	}
#endif // !NODEBUG	
}

void Stage_Element::Update(Player* player)
{
	//当たり判定演算範囲
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& e : element)
	{
		if (e == nullptr) continue;

		float x = e->GetLocation().x;
		float y = e->GetLocation().y;
		float w = e->GetArea().width;
		float h = e->GetArea().height;

		//ブロックの範囲を固定化
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// 画面内にあるMapChipオブジェクトだけUpdateする
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;


		e->Update(player);

	}
}

void Stage_Element::Draw() const
{

	//当たり判定演算範囲
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& e : element)
	{
		if (e == nullptr) continue;

		float x = e->GetLocation().x;
		float y = e->GetLocation().y;
		float w = e->GetArea().width;
		float h = e->GetArea().height;

		//ブロックの範囲を固定化
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// 画面内にあるMapChipオブジェクトだけUpdateする
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;


		e->Draw();

	}
}