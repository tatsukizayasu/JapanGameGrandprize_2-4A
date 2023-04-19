#include "HarpyBullet.h"
#include "CameraWork.h"

//ハーピィの遠距離攻撃の移動速度
#define HARPY_BULLET_SPEED 8

//ハーピィの遠距離ダメージ
#define HARPY_BULLET_DAMAGE 5

//-----------------------------------
//コンストラクタ
//-----------------------------------
HarpyBullet::HarpyBullet(const Location spawn_location, const Location player_location)
{

	type = ENEMY_TYPE::WIND;
	location = spawn_location;
	radius = 5;
	speed = HARPY_BULLET_SPEED;
	image = 0;
	damage = HARPY_BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
//デストラクタ
//-----------------------------------
HarpyBullet::~HarpyBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void HarpyBullet::Update()
{

	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画のみ
//-----------------------------------
void HarpyBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}
