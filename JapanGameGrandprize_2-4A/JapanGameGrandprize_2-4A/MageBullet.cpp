#include "MageBullet.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

#define MAGE_BULLET_SPEED 5
#define MAGE_BULLET_DAMAGE 2

//-----------------------------------
//コンストラクタ
//-----------------------------------
MageBullet::MageBullet(const ENEMY_TYPE type,
	const Location spawn_location, const Location player_location)
{

	location = spawn_location;
	radius = 6;
	speed = MAGE_BULLET_SPEED;
	this->type = type;

	image = 0;
	damage = MAGE_BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f((player_location.y - 10) - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
//デストラクタ
//-----------------------------------
MageBullet::~MageBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void MageBullet::Update()
{

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画
//-----------------------------------
void MageBullet::Draw() const
{

	Location draw_location = location; //描画座標
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	switch (type)
	{
	case ENEMY_TYPE::FIRE:
		DrawCircle(draw_location.x, draw_location.y, radius, 0xff0000, TRUE);
		break;
	case ENEMY_TYPE::WATER:
		DrawCircle(draw_location.x, draw_location.y, radius, 0x0000ff, TRUE);
		break;
	case ENEMY_TYPE::WIND:
		DrawCircle(draw_location.x, draw_location.y, radius, 0xffffff, TRUE);
		break;
	case ENEMY_TYPE::SOIL:
		DrawCircle(draw_location.x, draw_location.y, radius, 0xffff00, TRUE);
		break;
	case ENEMY_TYPE::NORMAL:
	case ENEMY_TYPE::THUNDER:
	default:
		break;
	}
}