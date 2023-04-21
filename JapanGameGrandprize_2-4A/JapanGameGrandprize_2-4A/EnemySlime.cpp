#include "EnemySlime.h"
#include "dxlib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include "Stage/Stage.h"

#define SLIME_ATTACK_DISTANCE_Y 15
#define SLIME_ATTACK_SPEED 5

//移動速度
#define SLIME_SPEED 2
#define SLIME_ATTACK_DAMAGE 10

#define SLIME_MIN_DROP 1
#define SLIME_DROP 5

#define GROUND 1200
#define WAIT_TIME 30 //プレイヤーを見つけて攻撃するまでの時間

#define ONE_ROUND 360 //一周の角度
#define ROTATION_SPEED 15 //スライムが回転するスピード

#define SLIME_HP 75
EnemySlime::EnemySlime(Location spawn_location)
{

	attack = false;
	left_move = true;
	kind = ENEMY_KIND::SLIME;

	location = spawn_location;

	jump_distance = location;
	area.height = 56;
	area.width = 52;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	wait_time = 0;
	image_type = 0;
	image_change_time = 0;
	image_addition = 1;
	hp = SLIME_HP;
	speed = SLIME_SPEED;

	slime_attack = SLIME_ATTACK::BEFORE_ATTACK;

	type = new ENEMY_TYPE[1];

	type[0] = static_cast<ENEMY_TYPE>(1 + GetRand(3));

	state = ENEMY_STATE::IDOL;
	images = new int[7];
	 LoadDivGraph("Images/Enemy/mov_slime.png", 7, 7, 1, 102,61, images);
	slime_angle = 0;

	//ドロップアイテムの設定
	switch (type[0])
	{
	case ENEMY_TYPE::FIRE:
		drop_element = new ElementItem * [FIRE_DROP];
		drop_type_volume = FIRE_DROP;
		break;
	case ENEMY_TYPE::WATER:
		drop_element = new ElementItem * [WATER_DROP];
		drop_type_volume = WATER_DROP;
		break;
	case ENEMY_TYPE::WIND:
		drop_element = new ElementItem * [WIND_DROP];
		drop_type_volume = WIND_DROP;
		break;
	case ENEMY_TYPE::SOIL:
		drop_element = new ElementItem * [SOIL_DROP];
		drop_type_volume = SOIL_DROP;
		break;
	case ENEMY_TYPE::NORMAL:
	case ENEMY_TYPE::THUNDER:
	default:
		break;
	}

	int volume = 0;

	for (int i = 0; i < drop_type_volume; i++)
	{
		volume = SLIME_MIN_DROP + GetRand(SLIME_DROP);

		switch (type[0])
		{
		case ENEMY_TYPE::NORMAL:
			break;
		case ENEMY_TYPE::FIRE:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			break;
		case ENEMY_TYPE::WATER:
			if (i < 2)
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			}
			else
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			}
			break;
		case ENEMY_TYPE::WIND:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			break;
		case ENEMY_TYPE::SOIL:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			break;
		case ENEMY_TYPE::THUNDER:
			break;
		default:
			break;
		}

		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}
#ifdef _DEBUG
	old_state  = ENEMY_STATE::IDOL;
	attack_time = 0;
	debug_location = location;
#endif // _DEBUG
}

EnemySlime::~EnemySlime()
{

	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(images[i]);
	}

	delete[] images;
}

void EnemySlime::Update(const Player* player, const Stage* stage)
{

	Location old_location = location;	//前の座標
	HitMapChip hit_stage = { false,nullptr }; //ステージとの当たり判定

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
				speed = -speed;
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
				if (left_move)
				{
					speed = -SLIME_SPEED;
				}
				else
				{
					speed = SLIME_SPEED;
				}

				if (paralysis)
				{
					speed *= PARALYSIS_SPEED;
				}
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

		hit_stage = HitStage(stage);

		if (hit_stage.hit) //ステージとの当たり判定
		{
			location = old_location;
			attack = false;
			state = ENEMY_STATE::MOVE;
			if (left_move)
			{
				speed = -SLIME_SPEED;
			}
			else
			{
				speed = SLIME_SPEED;
			}
			if (paralysis)
			{
				speed *= PARALYSIS_SPEED;
			}
		}
		break;

	case ENEMY_STATE::DEATH:
		Death();
		break;

	default:
		break;
	}
	
	Paralysis();

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
		jump_distance.y = 15;
	}

	UpdateDamageLog();

}

void EnemySlime::Draw()const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	if (state != ENEMY_STATE::DEATH)
	{
		DrawHPBar(SLIME_HP);
	}
	DrawDamageLog();

	DrawRotaGraphF(draw_location.x, draw_location.y, 0.85, M_PI / 180 * slime_angle, images[image_type], TRUE, !left_move);
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void EnemySlime::Idol()
{

	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (left_move)
		{
			speed = -SLIME_SPEED;
		}
		else
		{
			speed = SLIME_SPEED;
		}
		if (paralysis)
		{
			speed *= PARALYSIS_SPEED;
		}
	}
}

//-----------------------------------
//移動
//-----------------------------------
void EnemySlime::Move(const Location player_location)
{

	float distance; //離れている距離

	//プレイヤーとの距離の計算
	distance = sqrtf(powf(player_location.x - location.x, 2) + powf(player_location.y - location.y, 2));

	if (distance < 120 &&
	  ((left_move && player_location.x <= location.x) ||
	  (!left_move && player_location.x >= location.x)))
	{
		if (++wait_time >= WAIT_TIME)
		{
			state = ENEMY_STATE::ATTACK;
			jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
			wait_time = 0;
		}
	}
	else
	{
		if (++image_change_time > 2)
		{
			image_type += image_addition;
			if (image_type == 6)image_addition = -1;
			else if(image_type == 0) image_addition = 1;
			image_change_time = 0;
		}

		location.x += speed;
		wait_time = 0;
	}
}

//-----------------------------------
//落下
//-----------------------------------
void EnemySlime::Fall()
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
void  EnemySlime::Attack(const Location player_location)
{

	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;

	if (left_move)
	{
		speed = -SLIME_ATTACK_SPEED;
	}
	else
	{
		speed = SLIME_ATTACK_SPEED;
	}

	location.x += speed;
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource EnemySlime::Hit()
{

	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (!attack)
	{
		attack = true;
		slime_attack = SLIME_ATTACK::AFTER_ATTACK;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = SLIME_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void EnemySlime::Death()
{

	can_delete = true;

	/*if (slime_angle >= (ONE_ROUND * 2.5) || slime_angle <= -(ONE_ROUND * 2.5))
	{
		can_delete = true;
	}
	else
	{
		if (location.y <= GROUND)
		{
			location.y -= (jump_distance.y / 3);
			jump_distance.y--;
		}
		if (left_move)
		{
			speed = SLIME_ATTACK_SPEED;
			slime_angle += ROTATION_SPEED;
		}
		else
		{
			speed = -SLIME_ATTACK_SPEED;
			slime_angle -= ROTATION_SPEED;
		}
		location.x += speed;
	}*/
}

//-----------------------------------
// プレイヤーの弾との当たり判定
//-----------------------------------
void EnemySlime::HitBullet(const BulletBase* bullet)
{

	int i = 0;
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
		damage = bullet->GetDamage() * RESISTANCE_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::RESISTANCE;
		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage() * WEAKNESS_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::WEAKNESS;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage() * WEAKNESS_DAMAGE;
		damage_log[i].congeniality = CONGENIALITY::WEAKNESS;
		break;
	case ATTRIBUTE::POISON:
		if (!poison)
		{
			poison_damage = bullet->GetDamage() * 0;
			poison_time = bullet->GetDebuffTime() * 0;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		if (!paralysis)
		{
			paralysis = true;
			paralysis_time = bullet->GetDebuffTime();
			speed *= PARALYSIS_SPEED;
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
//座標の取得
//-----------------------------------
Location EnemySlime::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// 更新(DotByDot)
//-----------------------------------
void EnemySlime::Update(const ENEMY_STATE state)
{
	if ((old_state != state) || (attack_time < 0))
	{
		location = debug_location;
	}
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		if (++image_change_time > 2)
		{
			image_type += image_addition;
			if (image_type == 6)
			{
				image_addition = -1;
			}
			else if (image_type == 0)
			{
				image_addition = 1;
			}
			image_change_time = 0;
		}
		break;
	case ENEMY_STATE::FALL:
		break;
	case ENEMY_STATE::ATTACK:
		if ((old_state != state) || (attack_time < 0))
		{
			jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
			attack_time = SLIME_ATTACK_DISTANCE_Y * 3;
			location = debug_location;
		}
		if (SLIME_ATTACK_DISTANCE_Y < attack_time)
		{
			location.y -= (jump_distance.y / 3);
			jump_distance.y--;
			if (left_move)
			{
				speed = -SLIME_ATTACK_SPEED;
			}
			else
			{
				speed = SLIME_ATTACK_SPEED;
			}
			location.x += speed;

		}
		attack_time--;

		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}
	old_state = state;
}

//-----------------------------------
//描画(DotByDot)
//-----------------------------------
void EnemySlime::DebugDraw()
{
	DrawRotaGraphF(location.x, location.y, 0.85,
		M_PI / 180 * slime_angle, images[image_type], TRUE, !left_move);

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xff0000, FALSE);
}
#endif //_DEBUG