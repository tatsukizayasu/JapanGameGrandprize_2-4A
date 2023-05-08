#include "DragonBullet.h"
#include "CameraWork.h"

//ドラゴンの遠距離攻撃の移動速度
#define BULLET_SPEED 10

//ドラゴンの遠距離ダメージ
#define BULLET_DAMAGE 30

//-----------------------------------
//コンストラクタ
//-----------------------------------
DragonBullet::DragonBullet(Location spawn_location, Location player_location)
{

	type = ENEMY_TYPE::FIRE;
	location = spawn_location;
	radius = 5;
	speed = BULLET_SPEED;
	image = 0;
	damage = BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
//デストラクタ
//-----------------------------------
DragonBullet::~DragonBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void DragonBullet::Update()
{

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画のみ
//-----------------------------------
void DragonBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}

