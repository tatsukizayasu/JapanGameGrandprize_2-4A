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
#define UNDEAD_SPEED -2

//ドロップ量(最小)
#define UNDEAD_MIN_DROP 0
//ドロップ量(最大)
#define UNDEAD_MAX_DROP 5


//-----------------------------------
// コンストラクタ
//-----------------------------------
Undead::Undead()
{
	/*初期化*/
	damage = 0;
	attack_interval = 0;
	attack = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;
	collider = new LineCollider();

	/*当たり判定の設定*/
	location.x = 1270.0f;
	location.y = 430.0f;
	area.width = 40;
	area.height = 80;

	//ドロップアイテムの設定
	drop_item = DropItem(*type, UNDEAD_MIN_DROP, UNDEAD_MAX_DROP);

	//腕の当たり判定の設定
	for (int i = 0; i < 2; i++)
	{
		arm[i].x = 1270.0f - (50 * i);
		arm[i].y = 460.0f;
		collider->SetLocation(arm[i], i);
	}	
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Undead::~Undead()
{
	delete type;
	delete collider;
}

//-----------------------------------
// 更新
//-----------------------------------
void Undead::Update()
{
	switch (state)
	{
	case UNDEAD_STATE::IDOL:
		if ((-area.width < location.x) && (location.x < SCREEN_WIDTH))
		{
			state = UNDEAD_STATE::MOVE;
		}
		break;
	case UNDEAD_STATE::MOVE:
		for (int i = 0; i < 2; i++)
		{
			arm[i].x += speed;
			collider->SetLocation(arm[i], i);
		}
		location.x += speed;

		if ((location.x < -area.width) || (SCREEN_WIDTH < location.x))
		{
			state == UNDEAD_STATE::IDOL;
		}
		break;
	case UNDEAD_STATE::ATTACK:
		Attack();
		break;
	case UNDEAD_STATE::DEATH:
		break;
	default:
		break;
	}

	if (attack_interval > 0)
	{
		attack_interval--;
	}

	
}

//-----------------------------------
// 攻撃
//-----------------------------------
void Undead::Attack()
{
	
	arm[1].x += 5 * cosf(attack * (180 / 30));
	arm[1].y += 5 * sinf(attack * (180 / 30));

	collider->SetLocation(arm[1], 1);
	if (++attack % 30 == 0)
	{
		state = UNDEAD_STATE::IDOL;
		attack_interval = ATTACK_INTERVAL;
	}

}

//-----------------------------------
// プレイヤーとの距離
//-----------------------------------
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

//-----------------------------------
// プレイヤーの弾との当たり判定
//-----------------------------------
void Undead::HitBullet(Bullet* bullet)
{
	
}

//-----------------------------------
// 描画
//-----------------------------------
void Undead::Draw() const
{
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0xffffff, TRUE);
	DrawLine(arm[0].x, arm[0].y, arm[1].x, arm[1].y, 0xffffff, 5);
}

LineCollider Undead::GetLineCollider() const
{
	return *collider;
}
