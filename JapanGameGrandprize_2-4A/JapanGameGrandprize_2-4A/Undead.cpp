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


#define UNDEAD_ATTACK_DAMAGE 10
//体力
#define UNDEAD_HP 100

//-----------------------------------
// コンストラクタ
//-----------------------------------
Undead::Undead()
{
	/*初期化*/
	can_delete = false;
	hp = 100;
	damage = 0;
	attack_interval = 0;
	speed = UNDEAD_SPEED;
	kind = ENEMY_KIND::UNDEAD;
	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::SOIL;
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;
	attack_time = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;

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
	case ENEMY_STATE::IDOL:
		if ((-area.width < screen_x) && (screen_x < SCREEN_WIDTH + area.width))
		{
			state = ENEMY_STATE::MOVE;
		}
		break;
	case ENEMY_STATE::MOVE:
		if ((screen_x < -area.width) || (SCREEN_WIDTH + area.width < screen_x))
		{
			state = ENEMY_STATE::IDOL;
		}
		break;
	case ENEMY_STATE::ATTACK:
		attack_time--;
		if (attack_time < 0)
		{
			state = ENEMY_STATE::MOVE;
			image = 0xffffff;
			attack_interval = ATTACK_INTERVAL;
		}
		break;
	case ENEMY_STATE::DEATH:
		can_delete = true;
		break;
	default:
		break;
	}

	if (attack_interval > 0)
	{
		attack_interval--;
	}

	Poison();

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
}


//-----------------------------------
// プレイヤーとの距離
//-----------------------------------
void Undead::DistancePlayer(const Location player_location)
{
	float distance; //離れている距離

	//プレイヤーとの距離の計算
	distance = sqrtf(powf(player_location.x - location.x, 2) + powf(player_location.y - location.y, 2));

	//攻撃範囲に入っているかつ攻撃までの時間が0以下だったら攻撃する
	if ((distance < ATTACK_DISTANCE) && (attack_interval <= 0))
	{
		state = ENEMY_STATE::ATTACK;
		attack_time = 20;
		image = 0xff0000;
	}
	else if(distance < TRACKING_DISTANCE) //一定範囲内だとプレイヤーを追いかける
	{
		if (player_location.x < location.x)
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
//アイドル状態
//-----------------------------------
void Undead::Idol()
{

}

//-----------------------------------
//移動
//-----------------------------------
void Undead::Move(const Location player_location)
{
	DistancePlayer(player_location);

	location.x += speed;
}

//-----------------------------------
//攻撃
//-----------------------------------
AttackResource Undead::Attack(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (HitBox(collider))
	{
		ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::NORMAL };
		ret.damage = UNDEAD_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}
	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void Undead::Death()
{

}

//-----------------------------------
// プレイヤーの弾との当たり判定
//-----------------------------------
void Undead::HitBullet(const BulletBase* bullet)
{
		switch (bullet->GetAttribute())
		{
		case ATTRIBUTE::NORMAL:
			hp -= bullet->GetDamage();
			break;
		case ATTRIBUTE::EXPLOSION:
			hp -= bullet->GetDamage();
			break;
		case ATTRIBUTE::MELT:
			hp -= bullet->GetDamage();
			break;
		case ATTRIBUTE::POISON:
			poison_damage = bullet->GetDamage();
			poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
			break;
		case ATTRIBUTE::PARALYSIS:
			paralysis_time = bullet->GetDebuffTime() * 0;
			break;
		case ATTRIBUTE::HEAL:
			break;
		default:
			break;
		}
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
