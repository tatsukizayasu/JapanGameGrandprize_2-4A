#include "WyvernBreath.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

int* WyvernBreath::images = nullptr;

#define WYVERN_BULLET_SPEED 7
#define WYVERN_BULLET_DAMAGE 5

//-----------------------------------
//コンストラクタ
//-----------------------------------
WyvernBreath
::WyvernBreath(const Location spawn_location, const Location player_location)
{

	location = spawn_location;
	radius = 14;
	speed = WYVERN_BULLET_SPEED;
	type = ENEMY_TYPE::FIRE;
	damage = WYVERN_BULLET_DAMAGE;

	direction = atan2f((player_location.y + 10) - location.y, (player_location.x + 10) - location.x);
	x_speed = static_cast<int>(speed * cosf(direction));
	y_speed = static_cast<int>(speed * sinf(direction));

	if (images == nullptr)
	{
		images = new int[9];
		LoadDivGraph("images/enemy/wyvern_breath.png", 9, 3, 3, 1200, 1200, images);
	}
	images_index = 0;
	frame_count = 0;

}

//-----------------------------------
//デストラクタ
//-----------------------------------
WyvernBreath::~WyvernBreath()
{
	
}

//-----------------------------------
//更新
//-----------------------------------
void WyvernBreath::Update()
{

	location.x += x_speed;
	location.y += y_speed;

	frame_count++;
	if (frame_count % 3 == 0)
	{
		images_index++;
		if (WYVERN_IMAGES_NUM <= images_index)
		{
			images_index = 0;
		}
	}
}

//-----------------------------------
//描画
//-----------------------------------
void WyvernBreath::Draw() const
{

	Location draw_location = location; //描画座標
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	DrawRotaGraphF(draw_location.x, draw_location.y, WYVERN_BREATH_EXTEND_RATE, 
		direction - M_PI_2, images[images_index], TRUE);
	
	
}

void WyvernBreath::DeleteImages()
{
	if (images != nullptr)
	{
		for (int i = 0; i < 9; i++)
		{
			DeleteGraph(images[i]);
		}
		delete[] images;
	}
}
