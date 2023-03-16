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

#define SLIME_MIN_DROP 0u
#define SLIME_MAX_DROP 3u

#define GROUND 1200
#define WAIT_TIME 30 //プレイヤーを見つけて攻撃するまでの時間

#define ONE_ROUND 360 //一周の角度
#define ROTATION_SPEED 15 //スライムが回転するスピード


EnemySlime::EnemySlime()
{
	attack = false;
	left_move = true;
	kind = ENEMY_KIND::SLIME;

	location.x = 3080.0;
	location.y = 980.0f;

	//location.x = 200.0;
	//location.y = 700.0f;

	area.height = 50;
	area.width = 50;
	wait_time = 0;
	image_type = 0;
	image_change_time = 0;
	hp = 15;
	speed = SLIME_SPEED;

	color = GetColor(0, 0, 255);

	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::WATER;

	state = ENEMY_STATE::IDOL;
	images = new int[7];
	 LoadDivGraph("Images/Enemy/mov_slime1.png", 7, 7, 1, 450,269, images);
	slime_angle = 0;

	//ドロップアイテムの設定
	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;

	for (int i = 0; i < WATER_DROP; i++)
	{
		volume = SLIME_MIN_DROP + GetRand(SLIME_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

}

EnemySlime::~EnemySlime()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete type;

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

		break;

	case ENEMY_STATE::FALL:
		Fall();
		hit_stage = HitStage(stage);

		if (hit_stage.hit) //ステージとの当たり判定
		{
			Location chip_location = hit_stage.chip->GetLocation();
			Area chip_area = hit_stage.chip->GetArea();

			STAGE_DIRECTION hit_direction; //当たったステージブロックの面
			hit_direction = HitDirection(hit_stage.chip);

			if (hit_direction == STAGE_DIRECTION::TOP)
			{
				location.y = chip_location.y - 
					(chip_area.height / 2)- (area.height / 2);
				state = ENEMY_STATE::MOVE;
				if (left_move)
				{
					speed = -SLIME_SPEED;
				}
				else
				{
					speed = SLIME_SPEED;
				}
			}
		}
		break;

	case ENEMY_STATE::ATTACK:

		Attack(player->GetLocation());

		hit_stage = HitStage(stage);

		if (hit_stage.hit) //ステージとの当たり判定
		{
			attack = false;
			state = ENEMY_STATE::MOVE;
			if (left_move) speed = -SLIME_SPEED;
			else speed = SLIME_SPEED;
		}
		break;

	case ENEMY_STATE::DEATH:
		Death();
		break;

	default:
		break;
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
		jump_distance.y = 15;
	}
}

void EnemySlime::Draw()const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawRotaGraphF(draw_location.x, draw_location.y, 0.23, M_PI / 180 * slime_angle, images[image_type], TRUE, !left_move);
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void EnemySlime::Idol()
{
	Location scroll; //画面スクロールを考慮したX座標
	Location camera = CameraWork::GetCamera(); //カメラ
	scroll = location - camera;

	if ((-area.width < scroll.x) && (scroll.x < SCREEN_WIDTH + area.width) &&
		(-area.height < scroll.y) && (scroll.y < SCREEN_HEIGHT + area.height))
	{
		state = ENEMY_STATE::MOVE;
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
			if (image_type < 6)image_type++;
			else image_type = 0;
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
	if (speed < GRAVITY)
	{
		speed += ENEMY_FALL_SPEED;
	}
	location.y += speed;
}

//-----------------------------------
//攻撃
//-----------------------------------
void  EnemySlime::Attack(Location player_location)
{
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;

	if (left_move) speed = -SLIME_ATTACK_SPEED;
	else speed = SLIME_ATTACK_SPEED;

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
	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
		break;
	case ATTRIBUTE::EXPLOSION:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
		break;
	case ATTRIBUTE::MELT:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
		break;
	case ATTRIBUTE::POISON:
		//poison_damage = bullet->GetDamage();
		//poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
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
//座標の取得
//-----------------------------------
Location EnemySlime::GetLocation() const
{
	return location;
}