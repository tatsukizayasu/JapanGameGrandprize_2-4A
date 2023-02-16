#include "DxLib.h"
#include "Item.h"

//色
#define WHITE_COLOR 0xffffff
#define LIGHT_BLUE_COLOR 0xafdfe4
#define GRAY_COLOR 0xc0c0c0
#define BLACK_COLOR 0x000000
#define YELLOW_COLOR 0xfcf16e
#define DARK_YELLOW_COLOR 0xffcc4e


#define RAND_LCOATION 25

//-----------------------------------
// コンストラクタ
//-----------------------------------
Item::Item()
{
	color = 0;
	location.x = 0;
	location.y = 0;
	radius = 0;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
Item::Item(ELEMENT_ITEM type, Location location)
{
	this->location = location;
	if (GetRand(1))
	{
		this->location.x += GetRand(RAND_LCOATION);
		this->location.y += GetRand(RAND_LCOATION);

	}
	else
	{
		this->location.x -= GetRand(RAND_LCOATION);
		this->location.y -= GetRand(RAND_LCOATION);
	}

	color = 0;
	radius = 0;

	switch (type)
	{
	case ELEMENT_ITEM::OXYGEN:
		color = WHITE_COLOR;
		radius = 8;
		break;
	case ELEMENT_ITEM::HYDROGEN:
		color = LIGHT_BLUE_COLOR;
		radius = 2;
		break;
	case ELEMENT_ITEM::NITROGEN:
		color = GRAY_COLOR;
		radius = 6;
		break;
	case ELEMENT_ITEM::CARBON:
		color = BLACK_COLOR;
		radius = 4;
		break;
	case ELEMENT_ITEM::SULFUR:
		color = YELLOW_COLOR;
		radius = 10;
		break;
	case ELEMENT_ITEM::CHLORINE:
		color = DARK_YELLOW_COLOR;
		radius = 12;
		break;
	case ELEMENT_ITEM::URANIUM:
		break;
	case ELEMENT_ITEM::NONE:
		break;
	default:
		break;
	}
}

//-----------------------------------
// 更新
//-----------------------------------
void Item::Update()
{

}

//-----------------------------------
//描画
//-----------------------------------
void Item::Draw()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	//DrawCircleAA(location.x, location.y, radius, 32, color, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
