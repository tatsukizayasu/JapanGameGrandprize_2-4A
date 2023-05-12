#include "SlimeBossBullet.h"
#include "CameraWork.h"

//スライムボスの遠距離攻撃の移動速度
#define BULLET_SPEED 10

//スライムボスの遠距離ダメージ
#define BULLET_DAMAGE 20
#define BULLET_RADIUS 12

//-----------------------------------
//コンストラクタ
//-----------------------------------
SlimeBossBullet::SlimeBossBullet(Location spawn_location, Location player_location)
{

	type = ENEMY_TYPE::WATER;
	location = spawn_location;
	location.y += 18;
	radius = BULLET_RADIUS;
	//speed = BULLET_SPEED;
	damage = BULLET_DAMAGE;
	float radian; //角度
	gravity_power = 0;

	x_speed = -((location.x - player_location.x) / 60);
	y_speed = BULLET_SPEED;

	color = GetColor(24, 168, 203);
}

//-----------------------------------
//デストラクタ
//-----------------------------------
SlimeBossBullet::~SlimeBossBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void SlimeBossBullet::Update()
{
	gravity_power++;
	y_speed = (-BULLET_SPEED + (gravity_power / 3));

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画のみ
//-----------------------------------
void SlimeBossBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, color, TRUE);
}

