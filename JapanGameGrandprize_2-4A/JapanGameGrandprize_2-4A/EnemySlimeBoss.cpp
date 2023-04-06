#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlimeBoss.h"
#include"Player.h"
#include"Stage/Stage.h"

#define SLIME_MIN_DROP 0u
#define SLIME_MAX_DROP 3u

#define SLIME_BOSS_SPEED 5
#define SLIME_BOSS_ATTACK_DAMAGE 10
#define SLIME_BOSS_JUMP_DISTANCE 30

EnemySlimeBoss::EnemySlimeBoss(Location spawn_location)
{
	location = spawn_location;

	area.height = 50;
	area.width = 50;

	slime_boss_jump_distance = SLIME_BOSS_JUMP_DISTANCE;

	for (int i = 0; i < BODY_MAX; i++)
	{
		slime_boss_body[i] = new SlimeBossBody(16300, 300);
	}

	for (int i = 0; i < DATA; i++)
	{
		location_data[i].x = 16300;
		location_data[i].y = 300;
	}

	state = ENEMY_STATE::FALL;

	left_move = false;
	if (left_move)speed = -SLIME_BOSS_SPEED;
	else speed = SLIME_BOSS_SPEED;

	kind = ENEMY_KIND::SLIME;

	slime_boss_jump_distance = SLIME_BOSS_JUMP_DISTANCE;

	hp = 30;
	speed_y = -3;

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;

	//ドロップアイテムの設定

	int slime_min_drop = 5;
	int slime_drop = 10;

	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;

	for (int i = 0; i < WATER_DROP; i++)
	{
		volume = slime_min_drop + GetRand(slime_drop);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}
}

EnemySlimeBoss::~EnemySlimeBoss()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

	for (int i = 0; i < BODY_MAX; i++)
	{
		delete slime_boss_body[i];
	}
}


void EnemySlimeBoss::Update(const Player* player, const Stage* stage)
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

			if ((hit_direction == STAGE_DIRECTION::LEFT) || (hit_direction == STAGE_DIRECTION::RIGHT))
			{
				left_move = !left_move;
				if (left_move)speed = -SLIME_BOSS_SPEED;
				else speed = SLIME_BOSS_SPEED;
			}
			/*if (ScreenOut())
			{
				state = ENEMY_STATE::IDOL;
				speed = 0;
			}*/
		}
		else
		{
			state = ENEMY_STATE::FALL;
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
					(chip_area.height / 2) - (area.height / 2);

				state = ENEMY_STATE::MOVE;

				if (left_move)speed = -SLIME_BOSS_SPEED;
				else speed = SLIME_BOSS_SPEED;

			}

		}
		/*if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
		}*/
		break;

	case ENEMY_STATE::ATTACK:

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
	}

	for (int i = 0; i < BODY_MAX; i++)
	{
		slime_boss_body[i]->SetLocation(location_data[(DATA / BODY_MAX) * i]);
	}


	Location now = location;
	Location old;

	for (int i = 0; i < DATA; i++)
	{
		old.x = location_data[i].x;
		old.y = location_data[i].y;

		location_data[i].x = now.x;
		location_data[i].y = now.y;

		now.x = old.x;
		now.y = old.y;
	}
}

void EnemySlimeBoss::Draw()const
{
	if (can_delete == false)
	{
		for (int i = 0; i < BODY_MAX; i++)
		{
			slime_boss_body[i]->Draw();
		}
	}

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, 25, 0xff0000, true, true);

	DrawFormatString(0, 0, 0xffffff, "%d", state);
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void EnemySlimeBoss::Idol()
{
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (left_move)
		{
			speed = -SLIME_BOSS_SPEED;
		}
		else
		{
			speed = SLIME_BOSS_SPEED;
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
void EnemySlimeBoss::Move(const Location player_location)
{
	location.x += speed;
}

//-----------------------------------
//落下
//-----------------------------------
void EnemySlimeBoss::Fall()
{
	location.y += speed_y;

	if (speed_y < GRAVITY)
	{
		speed_y += ENEMY_FALL_SPEED;
	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void  EnemySlimeBoss::Attack(Location player_location)
{
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource EnemySlimeBoss::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void EnemySlimeBoss::Death()
{
	can_delete = true;
}

//-----------------------------------
// プレイヤーの弾との当たり判定
//-----------------------------------
void EnemySlimeBoss::HitBullet(const BulletBase* bullet)
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
Location EnemySlimeBoss::GetLocation() const
{
	return location;
}


#ifdef _DEBUG
//-----------------------------------
// 更新(DotByDot)
//-----------------------------------
void EnemySlimeBoss::Update(const ENEMY_STATE state)
{
	if ((old_state != state))
	{
		location = debug_location;
	}


	old_state = state;
}

//-----------------------------------
//描画(DotByDot)
//-----------------------------------
void EnemySlimeBoss::DebugDraw()
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, 15, 0xff0000, true, true);
}
#endif //_DEBUG

//#ifdef _DEBUG
////-----------------------------------
//// 更新(DotByDot)
////-----------------------------------
//void EnemySlime::Update(const ENEMY_STATE state)
//{
//	if ((old_state != state) || (attack_time < 0))
//	{
//		location = debug_location;
//	}
//	switch (state)
//	{
//	case ENEMY_STATE::IDOL:
//		break;
//	case ENEMY_STATE::MOVE:
//		if (++image_change_time > 2)
//		{
//			image_type += image_addition;
//			if (image_type == 6)
//			{
//				image_addition = -1;
//			}
//			else if (image_type == 0)
//			{
//				image_addition = 1;
//			}
//			image_change_time = 0;
//		}
//		break;
//	case ENEMY_STATE::FALL:
//		break;
//	case ENEMY_STATE::ATTACK:
//		if ((old_state != state) || (attack_time < 0))
//		{
//			jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
//			attack_time = SLIME_ATTACK_DISTANCE_Y * 3;
//			location = debug_location;
//		}
//		if (SLIME_ATTACK_DISTANCE_Y < attack_time)
//		{
//			location.y -= (jump_distance.y / 3);
//			jump_distance.y--;
//			if (left_move)
//			{
//				speed = -SLIME_ATTACK_SPEED;
//			}
//			else
//			{
//				speed = SLIME_ATTACK_SPEED;
//			}
//			location.x += speed;
//
//		}
//		attack_time--;
//
//		break;
//	case ENEMY_STATE::DEATH:
//		break;
//	default:
//		break;
//	}
//	old_state = state;
//}
//
////-----------------------------------
////描画(DotByDot)
////-----------------------------------
//void EnemySlime::DebugDraw()
//{
//	DrawRotaGraphF(location.x, location.y, 0.23,
//		M_PI / 180 * slime_angle, images[image_type], TRUE, !left_move);
//
//	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
//		location.x + area.width / 2, location.y + area.height / 2,
//		0xff0000, FALSE);
//}
//#endif //_DEBUG