#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Item.h"

//色
#define WHITE_COLOR 0xffffff
#define LIGHT_BLUE_COLOR 0xafdfe4
#define GRAY_COLOR 0xc0c0c0
#define BLACK_COLOR 0x000000
#define YELLOW_COLOR 0xfcf16e
#define DARK_YELLOW_COLOR 0xffcc4e


#define RAND_LCOATION 25
#define ITEM_BASE_SPEED 10

//-----------------------------------
// コンストラクタ
//-----------------------------------
Item::Item()
{
	color = 0;
	speed = 0;
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
	speed = ITEM_BASE_SPEED;

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
void Item::Update(Player* player)
{
	float radian; //角度
	//プレイヤーとアイテムの角度の計算
	radian = atan2f(player->GetLocation().y - location.y, player->GetLocation().x - location.x);

	location.x += static_cast<int>(speed * cosf(radian));
	location.y += static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
//描画
//-----------------------------------
void Item::Draw()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawCircle(static_cast<int>(location.x), static_cast<int>(location.y), radius, color, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
