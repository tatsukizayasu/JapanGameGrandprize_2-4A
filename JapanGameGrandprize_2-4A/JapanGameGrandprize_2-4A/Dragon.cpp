#include "Dragon.h"
#include "CameraWork.h"
#include "DxLib.h"

//ドラゴンの画像サイズ(未定、画像が出来次第調整）
#define DRAGON_SIZE_X 40
#define DRAGON_SIZE_Y 80

//魔法攻撃した時の硬直時間
#define MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define PHYSICAL_STANDBY 100

//ドラゴンの攻撃力
#define ATTACK_DAMAGE 20F  //float型

//ドロップ量(最小)
#define MIN_DROP 40

//ドロップ量(最大)
#define MAX_DROP 60

Dragon::Dragon(Location spawn_location)
{
	location = spawn_location;

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
//接近攻撃時の噛みつき
//-----------------------------------
void Dragon::DiteMove(const Location player_location)
{

}

//-----------------------------------
//接近攻撃時の噛みつき
//-----------------------------------
void Dragon::TailMove(const Location player_location)
{

}

//-----------------------------------
//遠距離攻撃（ブレス）
//-----------------------------------
void Dragon::DreathMove(const Location player_location)
{

}


void Dragon::RoarMove(const Location player_location)
{

}

//-----------------------------------
//攻撃が当たったのか
//-----------------------------------
AttackResource Dragon::Hit()
{
	return AttackResource();
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

}

//-----------------------------------
//プレイヤーの弾丸との当たり判定
//-----------------------------------
void Dragon::HitBullet(const BulletBase* bullet)
{

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