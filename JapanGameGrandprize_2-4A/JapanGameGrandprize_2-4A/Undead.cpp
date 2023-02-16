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
#define UNDEAD_MIN_DROP 0u
//ドロップ量(最大)
#define UNDEAD_MAX_DROP 5u

//ドロップする種類数
#define UNDEAD_DROP 4

//体力
#define UNDEAD_HP 100

//-----------------------------------
// コンストラクタ
//-----------------------------------
Undead::Undead(Player* player)
{
	/*初期化*/
	hp = 0;
	damage = 0;
	attack_interval = 0;
	attack = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	attack_type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;
	drop_volume = 0;

	/*当たり判定の設定*/
	location.x = 640.0f;
	location.y = 430.0f;
	area.width = 40;
	area.height = 80;

	//ドロップアイテムの設定
	drop_element = new ElementItem * [UNDEAD_DROP];

	int volume = 0;
	for (int i = 0; i < UNDEAD_DROP; i++)
	{
		volume = UNDEAD_MIN_DROP + GetRand(UNDEAD_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	//ドロップアイテムの初期化
	drop_item = new Item * [drop_volume];
	for (int i = 0; i < static_cast<int>(drop_volume); i++)
	{
		drop_item[i] = nullptr;
	}

	this->player = player;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Undead::~Undead()
{
	for (int i = 0; i < UNDEAD_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;

	for (int i = 0; i < drop_volume; i++)
	{
		delete drop_item[i];
	}
	delete[] drop_item;

	delete type;
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
		DistancePlayer();

		location.x += speed;

		if ((location.x < -area.width) || (SCREEN_WIDTH < location.x))
		{
			state = UNDEAD_STATE::IDOL;
		}
		break;
	case UNDEAD_STATE::ATTACK:
		break;
	case UNDEAD_STATE::DEATH:
		for (int i = 0; i < drop_volume; i++)
		{
			if (drop_item[i] == nullptr)
			{
				break;
			}

			drop_item[i]->Update(player);
		}
		break;
	default:
		break;
	}

	if (attack_interval > 0)
	{
		attack_interval--;
	}

	if (CheckHp() && (state != UNDEAD_STATE::DEATH))
	{
		state = UNDEAD_STATE::DEATH;
		CreateDropItem(UNDEAD_DROP,location);
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
	if (state != UNDEAD_STATE::DEATH)
	{
		DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0xffffff, TRUE);
	}
	else
	{
		for (int i = 0; i < drop_volume; i++)
		{
			if (drop_item[i] == nullptr)
			{
				break;
			}
			drop_item[i]->Draw();
		}
	}
}

//-----------------------------------
//状態の取得
//-----------------------------------
UNDEAD_STATE Undead::GetState() const
{
	return state;
}
