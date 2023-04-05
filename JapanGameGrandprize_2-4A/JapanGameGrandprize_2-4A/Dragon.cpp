#include "Dragon.h"
#include "CameraWork.h"
#include"BulletManager.h"
#include "DxLib.h"

//ドラゴンの画像サイズ(未定、画像が出来次第調整）
#define DRAGON_SIZE_X 40
#define DRAGON_SIZE_Y 80

//魔法攻撃した時の硬直時間
#define MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define PHYSICAL_STANDBY 100

//ドラゴンの攻撃力(攻撃別）
//尻尾攻撃
#define ATTACK_TAIL 20

//噛みつく
#define ATTACK_DITE 20 

//接近攻撃の範囲
#define MELEE_ATTACK 150

//ドロップ量(最小)
#define MIN_DROP 40

//ドロップ量(最大)
#define MAX_DROP 60

Dragon::Dragon(Location spawn_location)
{
	location = spawn_location;
	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	area.height = DRAGON_SIZE_Y;
	area.width = DRAGON_SIZE_X;

	animation = 0;
	animation_time = 0;
	hp = 500; 	
	speed = 0; 

	can_delete = false;
	left_move = true;

	kind = ENEMY_KIND::DRAGON;
	type = new ENEMY_TYPE[3];
	type[0] = ENEMY_TYPE::FIRE;
	type[1] = ENEMY_TYPE::WIND;
	type[2] = ENEMY_TYPE::THUNDER;

	state = ENEMY_STATE::IDOL;

	attack_state = DRAGON_ATTACK::NONE;

	//ドロップアイテムの設定
	drop_element = new ElementItem * [THUNDER_DROP];
	drop_type_volume = THUNDER_DROP;

	int volume = 0;
	for (int i = 0; i < THUNDER_DROP; i++)
	{
		volume = MIN_DROP + GetRand(MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}
}

Dragon::~Dragon()
{
	delete[] type;

	for (int i = 0; i < THUNDER_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;
}

void Dragon::Update(const class Player* player, const class Stage* stage)
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
		break;
	case ENEMY_STATE::FALL:
		Fall();
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

	hit_stage = HitStage(stage);
	if (hit_stage.hit) //ステージとの当たり判定
	{
		STAGE_DIRECTION hit_direction; //当たったステージブロックの面
		hit_direction = HitDirection(hit_stage.chip);

		if (hit_direction == STAGE_DIRECTION::TOP)
		{
			location = old_location;
		}
		if ((hit_direction == STAGE_DIRECTION::RIGHT) || (hit_direction == STAGE_DIRECTION::LEFT))
		{
			location = old_location;
			left_move = !left_move;
		}

	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
}

//-----------------------------------
//描画
//-----------------------------------
void Dragon::Draw() const
{
	//スクロールに合わせて描画
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2,
		GetColor(255, 0, 0), TRUE);

}

//-----------------------------------
//アイドル状態
//-----------------------------------
void Dragon::Idol()
{

}

//-----------------------------------
//動き
//-----------------------------------
void Dragon::Move(const Location player_location)
{
	//プレイヤーとの距離計算
	int range = player_location.x - location.x;


	//プレイヤーが接近攻撃距離にいたら
	if (range <= MELEE_ATTACK && range >= -MELEE_ATTACK)
	{

	}
	//遠距離系の攻撃
	else
	{

	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void Dragon::Attack(const Location player_location)
{
	switch (attack_state)
	{
		
	case DRAGON_ATTACK::DITE://噛みつき
		DiteMove(player_location);
		break;
	case DRAGON_ATTACK::TAIL_ATTACK: //尻尾攻撃
		TailMove(player_location);
		break;
	case DRAGON_ATTACK::DREATH: //ブレス攻撃
		DreathMove(player_location);
		break;
	case DRAGON_ATTACK::ROAR: //咆哮した後に雷を降らせる
		RoarMove(player_location);
		break;
	case DRAGON_ATTACK::NONE:
	default:
		break;
	}
}

//-----------------------------------
//接近攻撃時の噛みつき(飛行しながら噛みつく）プレイヤーに向かっていく
//-----------------------------------
void Dragon::DiteMove(const Location player_location)
{

}

//-----------------------------------
//尻尾攻撃
//-----------------------------------
void Dragon::TailMove(const Location player_location)
{

}

//-----------------------------------
//遠距離攻撃（ブレス）
//-----------------------------------
void Dragon::DreathMove(const Location player_location)
{
	BulletManager::GetInstance()->CreateEnemyBullet
	(new DragonBullet(location, player_location));
}

//-----------------------------------
//遠距離攻撃（咆哮）
//-----------------------------------
void Dragon::RoarMove(const Location player_location)
{

}

//-----------------------------------
//攻撃が当たったのか
//-----------------------------------
AttackResource Dragon::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (attack_state == DRAGON_ATTACK::DITE && (!attack))
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = ATTACK_DITE;
		ret.type = attack_type;
		ret.type_count = 1;
	}

	if (attack_state == DRAGON_ATTACK::TAIL_ATTACK && (!attack))
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = ATTACK_TAIL;
		ret.type = attack_type;
		ret.type_count = 2;
	}

	return ret;
}

//-----------------------------------
//落下
//-----------------------------------
void Dragon::Fall()
{

}

//-----------------------------------
//死亡（倒された）
//-----------------------------------
void Dragon::Death()
{
	can_delete = true;
}

//-----------------------------------
//プレイヤーの弾丸との当たり判定
//-----------------------------------
void Dragon::HitBullet(const BulletBase* bullet)
{
	switch (bullet->GetAttribute()) //受けた化合物の属性
	{
	case ATTRIBUTE::NORMAL: //通常弾 
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE; //効きにくい
		break;
	case ATTRIBUTE::EXPLOSION: //爆発 
		hp -= bullet->GetDamage() * 0; //効かない
		break;
	case ATTRIBUTE::MELT: //溶かす 　通常
		hp -= bullet->GetDamage(); //通常ダメージ
		break;
	case ATTRIBUTE::POISON: //毒　
		if (!poison)
		{
			poison = true;
			poison_time = bullet->GetDebuffTime();
			poison_damage = bullet->GetDamage();
		}
		break;
	case ATTRIBUTE::PARALYSIS: //麻痺 弱点
		if (!paralysis)
		{
			paralysis = true;
			paralysis_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;  //弱点
		}
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
Location Dragon::GetLocation() const
{
	return Location();
}


#ifdef _DEBUG
//-----------------------------------
// 更新(DotByDot)
//-----------------------------------
void Dragon::Update(const ENEMY_STATE state)
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
void Dragon::DebugDraw()
{
	
}
#endif //_DEBUG