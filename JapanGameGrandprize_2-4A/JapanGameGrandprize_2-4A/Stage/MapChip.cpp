#include "DxLib.h"
#include "MapChip.h"
#include "../CameraWork.h"
		
#define		COLLLISION_DEBUG		//当たり判定デバック

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

	collision_dir = { 0,0 };
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
void MapChip::Update(Player* player)
{
	if (HitBox(player)) 
	{
		//上
		if (location.y < player->GetLocation().y) 
		{
			collision_dir.y = 1;
		}
		//下
		else if (location.y > player->GetLocation().y)
		{
			collision_dir.y = -1;
		}

		//右
		if (location.x > player->GetLocation().x) 
		{
			collision_dir.x = 1;
		}
		//左
		else if (location.x < player->GetLocation().x) 
		{
			collision_dir.x = -1;
		}
	}
}

//-----------------------------------
// 描画
//-----------------------------------
void MapChip::Draw()const
{
	//画像がない又はエラーの場合は描画しない
	if (image == 0) { return; }

	//printfDx("camera_x:%f\tcamera_y:%f\n", CameraWork::GetCamera().x, CameraWork::GetCamera().y);
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	DrawRotaGraphF(x, y, ex_rate, 0, image, TRUE);
#ifdef _SHOW_COLLISION
	DrawCollision();
#endif

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
