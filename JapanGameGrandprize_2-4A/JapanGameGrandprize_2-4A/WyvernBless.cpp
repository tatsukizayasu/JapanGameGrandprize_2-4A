#include "WyvernBless.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

#define WYVERN_BULLET_SPEED 5
#define WYVERN_BULLET_DAMAGE 5

//-----------------------------------
//コンストラクタ
//-----------------------------------
WyvernBless::WyvernBless(const Location spawn_location, const Location player_location)
{

	location = spawn_location;
	radius = 14;
	speed = WYVERN_BULLET_SPEED;
	type = ENEMY_TYPE::FIRE;

	image = 0;
	damage = WYVERN_BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f((player_location.y + 10) - location.y, (player_location.x + 10)- location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
}

//-----------------------------------
//デストラクタ
//-----------------------------------
WyvernBless::~WyvernBless()
{

}

//-----------------------------------
//更新
//-----------------------------------
void WyvernBless::Update()
{

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画
//-----------------------------------
void WyvernBless::Draw() const
{

	Location draw_location = location; //描画座標
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, radius, 0xff0000, TRUE);
	
}