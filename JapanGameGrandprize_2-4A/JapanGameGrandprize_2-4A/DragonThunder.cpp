#include "DragonThunder.h"
#include "CameraWork.h"

//雷の移動速度
#define BULLET_SPEED 20

//雷ダメージ
#define BULLET_DAMAGE 30

//雷待機時間（攻撃予測時間？）
#define ATTACK_TIME 360

#define STANDBY 4

#define MOVE 1

DragonThunder::DragonThunder(float x, float y)
{
	type = ENEMY_TYPE::THUNDER;
	location.x = x;
	location.y = y;
	radius = 15;
	speed = BULLET_SPEED;
	thunder_time = 0;
	LoadDivGraph("Images/Enemy/Doragon/lightning.png", 20, 2, 20, 383, 384, image);
	damage = BULLET_DAMAGE;
	attack = false;
	tick = 0;
	frame = 0;
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
		tick++;
		location.y += speed;

		if (tick % 2 == 0) {
			frame++;
		}

	}
	else
	{
		tick++;

		if (tick % 4 == 0) {
			frame++;
			if (frame > 7) {
				frame = 5;
				tick = 0;
			}
		}
	}

}

void DragonThunder::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	//DrawCircle(0, 0, radius, 0xffffff, TRUE);


	DrawRotaGraph(x, y, 0.5, 0, image[frame], TRUE, FALSE, FALSE);
}



