#include "DxLib.h"
#include "MapChip.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
MapChip::MapChip()
{
	image = LoadGraph("images/stage/no_image.png");
	location = {30,30};
	area = {60,60};
	image_size = { 600,600 };
	ex_rate = area.height / image_size.height;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
MapChip::MapChip(const int* p_image, Location location, Area area)
{
	this->location.x = location.x;
	this->location.y = location.y;

	this->area.width = area.width;
	this->area.height = area.height;

	image = *p_image;
	{
		int x;
		int y;
		GetGraphSize(image, &x, &y);
		if (x == y)
		{
			ex_rate = area.height / y;
		}
		else
		{
			ex_rate = MAP_CHIP_SIZE / y;
		}
		image_size.width = (float)x;
		image_size.height = (float)y;
	}


}

//-----------------------------------
// デストラクタ
//-----------------------------------
MapChip::~MapChip()
{

}

//-----------------------------------
// 更新
//-----------------------------------
void MapChip::Update()
{

}

//-----------------------------------
// 描画
//-----------------------------------
void MapChip::Draw()const
{
	DrawRotaGraphF(location.x, location.y, ex_rate, 0,image, TRUE);
}

//-----------------------------------
// 
//-----------------------------------


//-----------------------------------
// 
//-----------------------------------


//-----------------------------------
// 
//-----------------------------------
