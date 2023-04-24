#include "KrakenBullet.h"
#include "CameraWork.h"

//クラーケンの遠距離攻撃の移動速度
#define BULLET_SPEED 3

//クラーケンの遠距離ダメージ
#define BULLET_DAMAGE 45

//-----------------------------------
//コンストラクタ
//-----------------------------------
KrakenBullet::KrakenBullet(Location spawn_location, Location player_location)
{

	type = ENEMY_TYPE::WATER;
	location = spawn_location;
	location.y = location.y -150;
	radius = 50;
	speed = BULLET_SPEED;
	image = 0;
	damage = BULLET_DAMAGE;

	float distance = player_location.x - location.x;
	float distance_y = player_location.y - location.y;
	float vector = sqrt(distance * distance + distance_y * distance_y);
	float radian= distance / vector;
	float radian_y = distance_y / vector;

	x_speed = radian;
	y_speed = radian_y;
	game_tiem = 0;
	start_time = 0; 

	start_attack = false;


}

//-----------------------------------
//デストラクタ
//-----------------------------------
KrakenBullet::~KrakenBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void KrakenBullet::Update()
{
	if (start_attack == false)
	{
		if (++game_tiem % 60 == 0)
		{
			if (++start_time > 1)
			{
				start_attack = true;
			}
		}
	}
	else
	{
		location.x += x_speed * speed;
		location.y += y_speed * speed;
	}
}

//-----------------------------------
//描画のみ
//-----------------------------------
void KrakenBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, GetColor(0,0,255), TRUE);
}

