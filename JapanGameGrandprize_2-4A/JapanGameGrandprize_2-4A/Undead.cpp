#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Undead.h"
#include "Define.h"

//攻撃をする範囲
#define ATTACK_DISTANCE 50

//次の攻撃までの時間
#define ATTACK_INTERVAL 20

//追いかける範囲
#define TRACKING_DISTANCE 340

//歩くスピード
#define UNDEAD_SPEED 5

Undead::Undead()
{
	/*初期化*/
	damage = 0;
	attack_interval = 0;
	speed = UNDEAD_SPEED;
	location.x = 1270.0f;
	location.y = 430.0f;

	area.width = 40;
	area.height = 80;

	kind = ENEMY_KIND::UNDEAD;
	type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;

	collider = new LineCollider();
}

Undead::~Undead()
{
	delete collider;
}

void Undead::Update()
{
	switch (state)
	{
	case UNDEAD_STATE::IDOL:
		if (location.x < SCREEN_WIDTH)
		{
			state = UNDEAD_STATE::MOVE;
		}
		break;
	case UNDEAD_STATE::MOVE:
		location.x -= speed;
		break;
	case UNDEAD_STATE::ATTACK:
		Attack();
		break;
	case UNDEAD_STATE::DEATH:
		break;
	default:
		break;
	}

	
}


void Undead::Attack()
{
	Location arm; //腕先の座標
	arm = collider->GetLocation(1);


}

void Undead::DistancePlayer(Player* player)
{
	float distance; //離れている距離

	//プレイヤーとの距離の計算
	distance = sqrtf(powf(player->GetLocation().x - location.x, 2) + powf(player->GetLocation().y - location.y, 2));

	//攻撃範囲に入っているかつ攻撃までの時間が0以下だったら攻撃する
	if ((distance < ATTACK_DISTANCE) && (attack_interval <= 0))
	{
		state = UNDEAD_STATE::ATTACK;
	}
	else if(distance < TRACKING_DISTANCE) //一定範囲内だとプレイヤーを追いかける
	{
		if (player->GetLocation().x < location.x)
		{
			speed = UNDEAD_SPEED;
		}
		else
		{
			speed = -UNDEAD_SPEED;
		}
	}
	else
	{
		speed = UNDEAD_SPEED;
	}
}

void Undead::Draw() const
{
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0xffffff, TRUE);
	DrawFormatString(100, 100, 0x000000, "%d", static_cast<int>(state));
}

LineCollider Undead::GetLineCollider() const
{
	return *collider;
}
