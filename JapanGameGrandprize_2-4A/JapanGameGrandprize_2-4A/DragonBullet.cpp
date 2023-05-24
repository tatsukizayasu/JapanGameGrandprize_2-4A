#include "DragonBullet.h"
#include "CameraWork.h"
int DragonBullet::images[DRAGON_BULLET_IMAGES_NUM] = {};

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
	radius = 15;
	speed = BULLET_SPEED;
	damage = BULLET_DAMAGE;

	direction = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(direction));
	y_speed = static_cast<int>(speed * sinf(direction));
	if (images[0] == 0)
	{
		int* images_t = new int[20];
		LoadDivGraph("images/enemy/doragon/tktk_Fire_10.png"
			, 20, 5, 4, 192, 192, images);
		for (int i = 0; i < DRAGON_BULLET_IMAGES_NUM; i++)
		{
			images[i] = images_t[1 + i];
		}
		delete[] images_t;
	}
	
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
	DrawRotaGraphF(x, y, 1, direction - M_PI, images[7], TRUE);
}

