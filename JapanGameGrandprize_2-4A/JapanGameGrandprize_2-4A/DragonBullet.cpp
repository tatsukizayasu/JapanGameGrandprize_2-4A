#include "DragonBullet.h"
#include "CameraWork.h"
int DragonBullet::images[DRAGON_BULLET_IMAGES_NUM] = {};
const float DragonBullet::distance[DRAGON_BULLET_IMAGES_NUM] =
{
	62,38,19,4,-10,-20,-30,-37,-46 ,-54
};

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
		int ret = LoadDivGraph("images/enemy/doragon/tktk_Fire_10.png"
			, 20
			, 5
			, 4
			, DRAGON_BULLET_IMAGE_SIZE
			, DRAGON_BULLET_IMAGE_SIZE
			, images_t);
		if (ret == 0)
		{
			for (int i = 0; i < DRAGON_BULLET_IMAGES_NUM; i++)
			{
				images[i] = images_t[1 + i];
			}
		}
		delete[] images_t;
	}
	
	frame_count = 0;
	images_index = 0;
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

	frame_count++;
	if (frame_count % 6 == 0)
	{
		images_index++;
		if (DRAGON_BULLET_IMAGES_NUM <= images_index)
		{
			images_index -= 4;		//後ろの画像四枚でループさせる
		}
	}
}

//-----------------------------------
//描画のみ
//-----------------------------------
void DragonBullet::Draw() const
{

	float x, y;

	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawRotaGraph2F(
		x
		, y
		, DRAGON_BULLET_IMAGE_CENTER + distance[images_index]
		, DRAGON_BULLET_IMAGE_CENTER
		, 1, direction - M_PI
		, images[images_index], TRUE);
}

