#include "DragonThunder.h"
#include "CameraWork.h"

//雷の移動速度
#define BULLET_SPEED 30

//雷ダメージ
#define BULLET_DAMAGE 30

//雷待機時間（攻撃予測時間？）
#define ATTACK_TIME 120

DragonThunder::DragonThunder(float x, float y)
{
	type = ENEMY_TYPE::THUNDER;
	location.x = x;
	location.y = y;
	radius = 5;
	speed = BULLET_SPEED;
	thunder_time = 0;
	image = 0;
	damage = BULLET_DAMAGE;
	attack = false;
}


//-----------------------------------
//デストラクタ
//-----------------------------------
DragonThunder::~DragonThunder()
{

}

//-----------------------------------
//更新
//-----------------------------------
void DragonThunder::Update()
{
	if (++thunder_time % ATTACK_TIME == 0)
	{
		attack = true;
	}

	if (attack == true)
	{
		location.y += speed;
	}

}

//-----------------------------------
//描画のみ
//-----------------------------------
void DragonThunder::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
}
