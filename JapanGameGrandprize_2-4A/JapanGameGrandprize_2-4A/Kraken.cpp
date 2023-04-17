#include "Kraken.h"

#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Define.h"
#include "CameraWork.h"

//クラーケンの画像  (画像なし、適当な数字を入れます）
#define KRAKEN_X 100
#define KRAKEN_Y 100

//攻撃をする範囲


//次の攻撃までの時間


//歩くスピード


//ドロップ量(最小)
#define MIN_DROP 40

//ドロップ量(最大)
#define MAX_DROP 60

//攻撃力

//体力
#define KRAKEN_HP 400



//-----------------------------------
// コンストラクタ
//-----------------------------------
Kraken::Kraken(Location spawn_location)
{

	/*初期化*/
	can_delete = false;
	left_move = true;

	hp = 100;
	damage = 0;

	
	kind = ENEMY_KIND::KRAKEN;
	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::WATER;
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	location = spawn_location;
	/*当たり判定の設定*/
	area.width = KRAKEN_X;
	area.height = KRAKEN_Y;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	//ドロップアイテムの設定
	drop_element = new ElementItem * [WATER_DROP];
	drop_type_volume = WATER_DROP;

	int volume = 0;

	for (int i = 0; i < WATER_DROP; i++)
	{
		volume = MIN_DROP + GetRand(MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	InitDamageLog();
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Kraken::~Kraken()
{

	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

	delete[] images;

}

//-----------------------------------
// 更新
//-----------------------------------
void Kraken::Update(const Player* player, const Stage* stage)
{

	HitMapChip hit_stage = { false,nullptr }; //ステージとの当たり判定
	Location old_location = location; //移動前の座標
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());

		hit_stage = HitStage(stage);
		if (hit_stage.hit) //ステージとの当たり判定
		{
			STAGE_DIRECTION hit_direction; //当たったステージブロックの面
			hit_direction = HitDirection(hit_stage.chip);

			if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
			{
				location = old_location;
				left_move = !left_move;
			}
		}
		else
		{
			state = ENEMY_STATE::FALL;
			speed = 0;
		}

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
		}
		break;
	case ENEMY_STATE::FALL:
		Fall();

		hit_stage = HitStage(stage);

		if (hit_stage.hit) //ステージとの当たり判定
		{
			Location chip_location = hit_stage.chip->GetLocation();
			Area chip_area = hit_stage.chip->GetArea();

			location.y = chip_location.y -
				(chip_area.height / 2) - (area.height / 2);

			STAGE_DIRECTION hit_direction; //当たったステージブロックの面
			hit_direction = HitDirection(hit_stage.chip);

			if (hit_direction == STAGE_DIRECTION::TOP)
			{
				state = ENEMY_STATE::MOVE;
			}
		}

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
		}
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}

	Poison();

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
	UpdateDamageLog();
}


//-----------------------------------
//アイドル状態
//-----------------------------------
void  Kraken::Idol()
{

	
}

//-----------------------------------
//移動
//-----------------------------------
void Kraken::Move(const Location player_location)
{

	
}

//-----------------------------------
//落下
//-----------------------------------
void Kraken::Fall()
{

	location.y += speed;
	if (speed < GRAVITY)
	{
		speed += ENEMY_FALL_SPEED;
	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void  Kraken::Attack(const Location player_location)
{

	switch (attack_state)
	{
	case KRAKEN_ATTACK::TENTACLE_ATTACK: //触手攻撃
		break;
	case KRAKEN_ATTACK::BREATH: //ブレス攻撃
		break;
	case KRAKEN_ATTACK::HARD_ATTACK: //水の塊を落とす
		break;
	case KRAKEN_ATTACK::NONE: //ノーマル
	default:
		break;
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource Kraken::Hit()
{

	AttackResource ret = { 0,nullptr,0 }; //戻り値

	/*if (attack_state == KRAKEN_ATTACK::TENTACLE_ATTACK)
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = ATTACK_DITE;
		ret.type = attack_type;
		ret.type_count = 1;
	}*/

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void Kraken::Death()
{

	can_delete = true;
}

//-----------------------------------
// プレイヤーの弾との当たり判定
//-----------------------------------
void Kraken::HitBullet(const BulletBase* bullet)
{

	int i;
	int damage = 0;
	for (i = 0; i < LOG_NUM; i++)
	{
		if (!damage_log[i].log)
		{
			break;
		}
	}

	if (LOG_NUM <= i)
	{
		for (i = 0; i < LOG_NUM - 1; i++)
		{
			damage_log[i] = damage_log[i + 1];
		}
		i = LOG_NUM - 1;

	}

	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::POISON:
		if (!poison)
		{
			poison = true;
			poison_damage = bullet->GetDamage();
			poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		if (!paralysis)
		{
			paralysis_time = bullet->GetDebuffTime() * 0;
		}
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
	}

	damage_log[i].log = true;
	damage_log[i].time = LOG_TIME;
	damage_log[i].damage = damage;
	hp -= damage;
}


//-----------------------------------
// 描画
//-----------------------------------
void Kraken::Draw() const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	if (state != ENEMY_STATE::DEATH)
	{
		//DrawHPBar();
	}

	DrawDamageLog();

}

//-----------------------------------
//座標の取得
//-----------------------------------
Location Kraken::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// 更新(DotByDot)
//-----------------------------------
void Kraken::Update(const ENEMY_STATE state)
{

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		break;
	case ENEMY_STATE::FALL:
		break;
	case ENEMY_STATE::ATTACK:
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}
}

//-----------------------------------
//描画(DotByDot)
//-----------------------------------
void Kraken::DebugDraw()
{

}
#endif //_DEBUG
