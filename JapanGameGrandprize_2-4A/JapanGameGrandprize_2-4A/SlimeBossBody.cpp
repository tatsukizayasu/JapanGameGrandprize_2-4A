//#include "SlimeBossBody.h"
//#include "dxlib.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//#include "Player.h"
//#include "Stage/Stage.h"
//
//#define SLIME_BOSS_SPEED 5
//#define SLIME_BOSS_ATTACK_DAMAGE 10
//
//SlimeBossBody::SlimeBossBody(int x, int y, int speed, int hp, int slime_min_drop, int slime_drop, BODY_TYPE body_type)
//{
//	left_move = true;
//	kind = ENEMY_KIND::SLIME;
//
//	location.x = x;
//	location.y = y;
//
//	area.height = 50;
//	area.width = 50;
//
//	this->hp = hp;
//	this->speed = SLIME_BOSS_SPEED;
//
//	this->body_type = body_type;
//
//	type = new ENEMY_TYPE;
//	*type = ENEMY_TYPE::WATER;
//
//	slimeboss_image = LoadGraph("Images/Enemy/Slime_.png");
//
//	//ドロップアイテムの設定
//	drop_element = new ElementItem * [SOIL_DROP];
//	drop_type_volume = SOIL_DROP;
//
//	int volume = 0;
//
//	for (int i = 0; i < WATER_DROP; i++)
//	{
//		volume = slime_min_drop + GetRand(slime_drop);
//		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
//		drop_element[i]->SetVolume(volume);
//		drop_volume += volume;
//	}
//
//	state = ENEMY_STATE::MOVE;
//}
//
//SlimeBossBody::~SlimeBossBody()
//{
//	for (int i = 0; i < SOIL_DROP; i++)
//	{
//		delete drop_element[i];
//	}
//
//	delete[] drop_element;
//
//	delete[] type;
//
//	for (int i = 0; i < 7; i++)
//	{
//		DeleteGraph(images[i]);
//	}
//
//	delete[] images;
//
//}
//
//void SlimeBossBody::Update(const Player* player, const Stage* stage)
//{
//	Location old_location = location;	//前の座標
//	HitMapChip hit_stage = { false,nullptr }; //ステージとの当たり判定
//
//	switch (state)
//	{
//	case ENEMY_STATE::IDOL:
//		Idol();
//		break;
//
//	case ENEMY_STATE::MOVE:
//
//		hit_stage = HitStage(stage);
//
//		if (hit_stage.hit) //ステージとの当たり判定
//		{
//			STAGE_DIRECTION hit_direction; //当たったステージブロックの面
//			hit_direction = HitDirection(hit_stage.chip);
//
//			if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
//			{
//				location = old_location;
//				left_move = !left_move;
//				speed = -speed;
//			}
//		}
//		else
//		{
//			state = ENEMY_STATE::FALL;
//			speed = 0;
//		}
//
//		if (ScreenOut())
//		{
//			state = ENEMY_STATE::IDOL;
//			speed = 0;
//		}
//
//		break;
//
//	case ENEMY_STATE::FALL:
//		Fall();
//
//		hit_stage = HitStage(stage);
//
//		if (hit_stage.hit) //ステージとの当たり判定
//		{
//			Location chip_location = hit_stage.chip->GetLocation();
//			Area chip_area = hit_stage.chip->GetArea();
//
//			STAGE_DIRECTION hit_direction; //当たったステージブロックの面
//			hit_direction = HitDirection(hit_stage.chip);
//
//			if (hit_direction == STAGE_DIRECTION::TOP)
//			{
//				location.y = chip_location.y -
//					(chip_area.height / 2) - (area.height / 2);
//				state = ENEMY_STATE::MOVE;
//				if (left_move)
//				{
//					speed = -SLIME_BOSS_SPEED;
//				}
//				else
//				{
//					speed = SLIME_BOSS_SPEED;
//				}
//			}
//		}
//
//		if (ScreenOut())
//		{
//			state = ENEMY_STATE::IDOL;
//			speed = 0;
//		}
//		break;
//
//	case ENEMY_STATE::ATTACK:
//
//		break;
//
//	case ENEMY_STATE::DEATH:
//		Death();
//		break;
//
//	default:
//		break;
//	}
//
//	if (CheckHp() && state != ENEMY_STATE::DEATH)
//	{
//		state = ENEMY_STATE::DEATH;
//	}
//}
//
//void SlimeBossBody::Draw()const
//{
//	Location draw_location = location;
//	Location camera = CameraWork::GetCamera();
//	draw_location = draw_location - camera;
//
//	DrawCircle(draw_location.x, draw_location.y, 15, 0xff0000, true, true);
//}
//
////-----------------------------------
////アイドル状態
////-----------------------------------
//void SlimeBossBody::Idol()
//{
//}
//
////-----------------------------------
////移動
////-----------------------------------
//void SlimeBossBody::Move(const Location player_location)
//{
//
//}
//
////-----------------------------------
////落下
////-----------------------------------
//void SlimeBossBody::Fall()
//{
//	location.y += speed;
//	if (speed < GRAVITY)
//	{
//		speed += ENEMY_FALL_SPEED;
//	}
//}
//
////-----------------------------------
////攻撃
////-----------------------------------
//void  SlimeBossBody::Attack(Location player_location)
//{
//}
//
////-----------------------------------
////攻撃が当たっているか
////-----------------------------------
//AttackResource SlimeBossBody::Hit()
//{
//	AttackResource ret = { 0,nullptr,0 }; //戻り値
//
//	if (!attack)
//	{
//		attack = true;
//		ENEMY_TYPE attack_type[1] = { *type };
//		ret.damage = SLIME_BOSS_ATTACK_DAMAGE;
//		ret.type = attack_type;
//		ret.type_count = 1;
//	}
//
//	return ret;
//}
//
////-----------------------------------
////死亡
////-----------------------------------
//void SlimeBossBody::Death()
//{
//	can_delete = true;
//}
//
////-----------------------------------
//// プレイヤーの弾との当たり判定
////-----------------------------------
//void SlimeBossBody::HitBullet(const BulletBase* bullet)
//{
//	switch (bullet->GetAttribute())
//	{
//	case ATTRIBUTE::NORMAL:
//		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
//		break;
//	case ATTRIBUTE::EXPLOSION:
//		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
//		break;
//	case ATTRIBUTE::MELT:
//		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
//		break;
//	case ATTRIBUTE::POISON:
//		//poison_damage = bullet->GetDamage();
//		//poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
//		break;
//	case ATTRIBUTE::PARALYSIS:
//		paralysis_time = bullet->GetDebuffTime() * 0;
//		break;
//	case ATTRIBUTE::HEAL:
//		break;
//	default:
//		break;
//	}
//}
//
////-----------------------------------
////座標の取得
////-----------------------------------
//Location SlimeBossBody::GetLocation() const
//{
//	return location;
//}
//
//void SlimeBossBody::SetLocation(Location location)
//{
//	this->location.x = location.x;
//	this->location.y = location.y;
//}