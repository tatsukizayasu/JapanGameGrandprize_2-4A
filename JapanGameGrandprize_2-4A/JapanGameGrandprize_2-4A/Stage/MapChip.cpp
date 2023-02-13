#include "DxLib.h"
#include "MapChip.h"
#include "../CameraWork.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
MapChip::MapChip()
{
	location = { 30,30 };
	area = { 60,60 };
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
	location.x = location.x + CameraWork::GetCamera().x;
	location.y = location.y + CameraWork::GetCamera().y;
}

//-----------------------------------
// 描画
//-----------------------------------
void MapChip::Draw()const
{
	//printfDx("camera_x:%f\tcamera_y:%f\n", camera_x, camera_y);
	//float x = location.x + CameraWork::GetCamera().x;
	//float y = location.y + CameraWork::GetCamera().y;

	DrawRotaGraphF(location.x, location.y, ex_rate, 0, image, TRUE);
#ifdef _SHOW_COLLISION
	DrawCollision();
#endif
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
