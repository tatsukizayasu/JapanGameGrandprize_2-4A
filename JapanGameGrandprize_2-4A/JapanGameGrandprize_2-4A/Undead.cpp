#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Undead.h"
#include "Define.h"
#include "CameraWork.h"

//攻撃をする範囲
#define ATTACK_DISTANCE 50

//次の攻撃までの時間
#define ATTACK_INTERVAL 30

//追いかける範囲
#define TRACKING_DISTANCE 340

//歩くスピード
#define UNDEAD_SPEED -2

//ドロップ量
#define UNDEAD_MIN_DROP 0u
#define UNDEAD_MAX_DROP 5u



//体力
#define UNDEAD_HP 100

//-----------------------------------
// コンストラクタ
//-----------------------------------
Undead::Undead(Player* player)
{
	/*初期化*/
	can_delete = false;
	hp = 0;
	damage = 0;
	attack_interval = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;
	attack_time = 0;

	/*当たり判定の設定*/
	location.x = 640.0f;
	location.y = 430.0f;
	area.width = 40;
	area.height = 80;

	//ドロップアイテムの設定
	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;
	for (int i = 0; i < SOIL_DROP; i++)
	{
		volume = UNDEAD_MIN_DROP + GetRand(UNDEAD_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	this->player = player;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Undead::~Undead()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;

	delete type;
}

//-----------------------------------
// 更新
//-----------------------------------
void Undead::Update()
{
	float screen_x; //画面スクロールを考慮したX座標

	screen_x = location.x - CameraWork::GetCamera().x;

	switch (state)
	{
	case UNDEAD_STATE::IDOL:
		if ((-area.width < screen_x) && (screen_x < SCREEN_WIDTH + area.width))
		{
			state = UNDEAD_STATE::MOVE;
		}
		break;
	case UNDEAD_STATE::MOVE:
		DistancePlayer();

		location.x += speed;

		if ((screen_x < -area.width) || (SCREEN_WIDTH + area.width < screen_x))
		{
			state = UNDEAD_STATE::IDOL;
		}
		break;
	case UNDEAD_STATE::ATTACK:
		attack_time--;
		if (attack_time < 0)
		{
			state = UNDEAD_STATE::MOVE;
			image = 0xffffff;
			attack_interval = ATTACK_INTERVAL;
		}
		break;
	case UNDEAD_STATE::DEATH:
		can_delete = true;
		break;
	default:
		break;
	}

	if (attack_interval > 0)
	{
		attack_interval--;
	}

	if (CheckHp() && state != UNDEAD_STATE::DEATH)
	{
		state = UNDEAD_STATE::DEATH;
	}
}


//-----------------------------------
// プレイヤーとの距離
//-----------------------------------
void Undead::DistancePlayer()
{
	float distance; //離れている距離

	//プレイヤーとの距離の計算
	distance = sqrtf(powf(player->GetLocation().x - location.x, 2) + powf(player->GetLocation().y - location.y, 2));

	//攻撃範囲に入っているかつ攻撃までの時間が0以下だったら攻撃する
	if ((distance < ATTACK_DISTANCE) && (attack_interval <= 0))
	{
		state = UNDEAD_STATE::ATTACK;
		attack_time = 20;
		image = 0xff0000;
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
void Undead::HitBullet(BulletBase* bullet)
{
	
}

//-----------------------------------
// 描画
//-----------------------------------
void Undead::Draw() const
{
	Location draw_location; //描画用の座標

	draw_location.x = location.x - CameraWork::GetCamera().x;
	draw_location.y = location.y - CameraWork::GetCamera().y;

	DrawBox(draw_location.x, draw_location.y, draw_location.x + area.width, draw_location.y + area.height, image, TRUE);
}

//-----------------------------------
//状態の取得
//-----------------------------------
UNDEAD_STATE Undead::GetState() const
{
	return state;
}
