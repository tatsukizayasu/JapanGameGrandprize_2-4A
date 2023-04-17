#include "KrakenBullet.h"
#include "CameraWork.h"

//クラーケンの遠距離攻撃の移動速度
#define BULLET_SPEED 1

//クラーケンの遠距離ダメージ
#define BULLET_DAMAGE 45

//-----------------------------------
//コンストラクタ
//-----------------------------------
KrakenBullet::KrakenBullet(Location spawn_location, Location player_location)
{

	type = ENEMY_TYPE::WATER;
	location = spawn_location;
	radius = 10;
	speed = BULLET_SPEED;
	image = 0;
	damage = BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
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

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画のみ
//-----------------------------------
void KrakenBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}

