#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "MageBullet.h"
#include "CameraWork.h"

#define MAGE_BULLET_SPEED 5
#define MAGE_BULLET_DAMAGE 2

//-----------------------------------
//コンストラクタ
//-----------------------------------
MageBullet::MageBullet(ENEMY_TYPE type, Location spawn_location, Location player_location)
{
	location = spawn_location;
	radius = 6;
	speed = MAGE_BULLET_SPEED;
	this->type = type;

	image = 0;
	damage = MAGE_BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
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
	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;
	switch (type)
	{
	case ENEMY_TYPE::NORMAL:
		break;
	case ENEMY_TYPE::FIRE:
		DrawCircle(x, y, radius, 0xff0000, TRUE);
		break;
	case ENEMY_TYPE::WATER:
		DrawCircle(x, y, radius, 0x0000ff, TRUE);
		break;
	case ENEMY_TYPE::WIND:
		DrawCircle(x,y, radius, 0xffffff, TRUE);
		break;
	case ENEMY_TYPE::SOIL:
		DrawCircle(x, y, radius, 0xffff00, TRUE);
		break;
	case ENEMY_TYPE::THUNDER:
		break;
	default:
		break;
	}
}