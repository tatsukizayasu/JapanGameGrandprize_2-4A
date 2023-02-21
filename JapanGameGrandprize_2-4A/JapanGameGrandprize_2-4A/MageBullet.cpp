#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "MageBullet.h"


#define MAGE_BULLET_SPEED 5

//-----------------------------------
//コンストラクタ
//-----------------------------------
MageBullet::MageBullet(ENEMY_TYPE type, Location spawn_location, Location player_location)
{
	location = spawn_location;
	speed = MAGE_BULLET_SPEED;
	this->type = type;

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
	switch (type)
	{
	case ENEMY_TYPE::NORMAL:
		break;
	case ENEMY_TYPE::FIRE:
		DrawCircle(location.x, location.y, 6, 0xff0000, TRUE);
		break;
	case ENEMY_TYPE::WATER:
		DrawCircle(location.x, location.y, 6, 0x00ff00, TRUE);
		break;
	case ENEMY_TYPE::WIND:
		DrawCircle(location.x, location.y, 6, 0x00ffff, TRUE);
		break;
	case ENEMY_TYPE::SOIL:
		DrawCircle(location.x, location.y, 6, 0x770077, TRUE);
		break;
	case ENEMY_TYPE::THUNDER:
		break;
	default:
		break;
	}
}