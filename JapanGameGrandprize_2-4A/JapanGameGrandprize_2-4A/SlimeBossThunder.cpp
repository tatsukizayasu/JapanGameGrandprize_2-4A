#include "SlimeBossThunder.h"
#include "CameraWork.h"

//スライムボスの遠距離攻撃の移動速度
#define BULLET_SPEED 15

//スライムボスの遠距離ダメージ
#define BULLET_DAMAGE 20
#define BULLET_RADIUS 25

#define ORIENTATION_TIME 10



//-----------------------------------
//コンストラクタ
//-----------------------------------
SlimeBossThunder::SlimeBossThunder(Location spawn_location, Location player_location)
{
	type = ENEMY_TYPE::THUNDER;
	location = player_location;
	location.y = player_location.y - 400;

	for (int i = 0; i < LOCATION_DATA; i++)
	{
		old_location[i] = location;
		old_radius[i] = BULLET_RADIUS;
	}

	radius = BULLET_RADIUS;
	speed = BULLET_SPEED;
	image = 0;
	damage = BULLET_DAMAGE;
	
	left_move = TRUE;

	y_speed = speed;
	if (left_move)x_speed = -(speed / 2);
	else x_speed = (speed / 2);

	orientation_time = ORIENTATION_TIME;
	data_switch = 0;
	
	color = GetColor(255, 255, 0);
}

//-----------------------------------
//デストラクタ
//-----------------------------------
SlimeBossThunder::~SlimeBossThunder()
{

}

//-----------------------------------
//更新
//-----------------------------------
void SlimeBossThunder::Update()
{
	if (--orientation_time <= 0)
	{
		left_move = !left_move;
		x_speed = -x_speed;
		orientation_time = ORIENTATION_TIME;
	}

	location.x += x_speed;
	location.y += y_speed;

	data_switch++;
	radius = BULLET_RADIUS - (data_switch / 2);

	if (data_switch < LOCATION_DATA)
	{
		old_location[data_switch] = location;
		old_radius[data_switch] = radius;
	}

}

//-----------------------------------
//描画のみ
//-----------------------------------
void SlimeBossThunder::Draw() const
{
	float x, y;

	for (int i = 0; i < LOCATION_DATA; i++)
	{
		x = old_location[i].x - CameraWork::GetCamera().x;
		y = old_location[i].y - CameraWork::GetCamera().y;

		DrawCircle(x, y, old_radius[i], color, TRUE);
	}
}

