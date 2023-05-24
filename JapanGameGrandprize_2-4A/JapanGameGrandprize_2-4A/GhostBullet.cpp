#include "GhostBullet.h"
#include "CameraWork.h"

#define GHOST_BULLET_SPEED 10
#define GHOST_BULLET_DAMAGE 10

//-----------------------------------
//コンストラクタ
//-----------------------------------
GhostBullet::GhostBullet(const Location spawn_location, const Location player_location)
{

	type = ENEMY_TYPE::WIND;
	location = spawn_location;
	radius = 33;
	frame = 0;
	angle = 0;
	tick = 0;
	speed = GHOST_BULLET_SPEED;
	image = LoadGraph("images/Enemy/Ghost/ghost.png");;
	damage = GHOST_BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
// デストラクタ
//-----------------------------------
GhostBullet::~GhostBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void GhostBullet::Update()
{

	location.x += x_speed;
	location.y += y_speed;

	tick++;
	if (tick == 1)
	{
		frame = 0;
	}
	if (tick % 3 == 0)
	{
		frame++;
		if (frame > 14)
		{
			tick = 0;
		}
	}
	else
	{
		frame++;
		if (frame > 10)
		{
			frame = 5;
		}
	}

	angle = (tick * 30) % 360;
	angle = angle * (M_PI / 180);
}

//-----------------------------------
//描画
//-----------------------------------
void GhostBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawRotaGraph(x, y, 0.4, angle, image, TRUE, FALSE, FALSE);

	//DrawCircle(x, y, radius, GetColor(255,0,255), FALSE);
}