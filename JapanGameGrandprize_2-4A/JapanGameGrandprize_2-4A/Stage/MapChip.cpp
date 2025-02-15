#include "DxLib.h"
#include "MapChip.h"
#include "../CameraWork.h"
		
//#define		COLLLISION_DEBUG		//当たり判定デバック

//-----------------------------------
// コンストラクタ
//-----------------------------------
MapChip::MapChip()
{
	collider_type =(int) COLLIDER::DEFAULT;
	location = { 30,30 };
	area = { 60,60 };
	image_size = { 600,600 };
	ex_rate = area.height / image_size.height;
	image = 0;
	angle = 0.0;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
MapChip::MapChip(const int* p_image, Location location, Area area)
{

	collider_type =(int) COLLIDER::DEFAULT;
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

	angle= 0.0;
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

	//画像がない又はエラーの場合は描画しない
	if (image == 0 or image == NULL) { return; }

	//printfDx("camera_x:%f\tcamera_y:%f\n", CameraWork::GetCamera().x, CameraWork::GetCamera().y);
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	
	DrawRotaGraphF(x, y, 1.0f, angle * (M_PI / 180), image, TRUE);
#ifdef COLLLISION_DEBUG

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	DrawBoxAA(x - (area.width / 2) - 1, y - (area.height / 2) - 1, x - (area.width / 2) + area.width + 1, y - (area.height / 2) + area.height + 1, 0x000000, FALSE, 0.5F);
	DrawBoxAA(x - (area.width / 2), y - (area.height / 2), x - (area.width / 2) + area.width, y - (area.height / 2) + area.height, 0xff0000, TRUE, 0.5F);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#endif // COLLLISION_DEBUG
}

//-----------------------------------
// 
//-----------------------------------