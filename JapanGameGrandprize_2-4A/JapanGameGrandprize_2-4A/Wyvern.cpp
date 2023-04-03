#include "Wyvern.h"
#include "Player.h"
#include "BulletManager.h"

//移動スピード
#define WYVERN_MOVE_SPEED 2
//強襲攻撃スピード
#define WYVERN_ASSAULT_SPEED 5

#define WYVERN_MIN_DROP 1
#define WYVERN_DROP 8

#define BLESS_INTERVAL 300
#define TRIPLE_BLESS_INTERVAL 600
#define ASSAULT_INTERVAL 480

//-----------------------------------
//コンストラクタ
//-----------------------------------
Wyvern::Wyvern(Location spawn_location)
{
	/*初期化*/
	can_delete = false;
	left_move = true;
	attack_end = false;
	attack = false;

	hp = 100;
	damage = 0;

	bless_interval = BLESS_INTERVAL;
	triple_bless_interval = TRIPLE_BLESS_INTERVAL;
	assault_interval = ASSAULT_INTERVAL;

	shot_rate = 0;
	assault_speed[0] = 0;
	assault_speed[1] = 0;
	image_argument = 0;
	speed = 0;
	kind = ENEMY_KIND::WYVERN;
	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::FIRE;
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	location = spawn_location;
	/*当たり判定の設定*/
	area.width = 40;
	area.height = 80;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	//ドロップアイテムの設定
	drop_element = new ElementItem * [FIRE_DROP];
	drop_type_volume = FIRE_DROP;

	int volume = 0;

	for (int i = 0; i < FIRE_DROP; i++)
	{
		volume = WYVERN_MIN_DROP + GetRand(WYVERN_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	images = nullptr;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
Wyvern::~Wyvern()
{
	delete[] images;
}

//-----------------------------------
//更新
//-----------------------------------
void Wyvern::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//前の座標

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());

		if (bless_interval < 0) //ブレスに移行
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::BLESS;
			break;
		}

		if (triple_bless_interval < 0) //トリプルブレスに移行
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::TRIPLE_BRACE;
			break;
		}

		if (assault_interval < 0) //アサルトに移行
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = WYVERN_ATTACK::ASSAULT;
			break;
		}
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
	Poison();
	Paralysis();

	if ((state != ENEMY_STATE::DEATH) && (state != ENEMY_STATE::IDOL))
	{

	}
	if (CheckHp() && (state != ENEMY_STATE::DEATH))
	{
		state = ENEMY_STATE::DEATH;
	}
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void Wyvern::Idol()
{
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (left_move)
		{
			speed = -WYVERN_MOVE_SPEED;
		}
		else
		{
			speed = WYVERN_MOVE_SPEED;
		}
	}
}

//-----------------------------------
//移動
//-----------------------------------
void Wyvern::Move(const Location player_location)
{
	if (ScreenOut())
	{
		state = ENEMY_STATE::IDOL;
	}
}

//-----------------------------------
//移動時のアニメーション
//-----------------------------------
void Wyvern::MoveAnimation()
{

}

//-----------------------------------
//落下
//-----------------------------------
void Wyvern::Fall()
{

}

//-----------------------------------
//攻撃
//-----------------------------------
void Wyvern::Attack(const Location)
{
	switch (attack_state)
	{
	case WYVERN_ATTACK::BLESS:
		break;
	case WYVERN_ATTACK::TRIPLE_BRACE:
		break;
	case WYVERN_ATTACK::ASSAULT:
		break;
	case WYVERN_ATTACK::NONE:
		break;
	default:
		break;
	}

	if(attack_end)
	{
		state = ENEMY_STATE::MOVE;
		switch (attack_state) //インターバルの設定
		{
		case WYVERN_ATTACK::BLESS:
			bless_interval = BLESS_INTERVAL;
			break;
		case WYVERN_ATTACK::TRIPLE_BRACE:
			triple_bless_interval = TRIPLE_BLESS_INTERVAL;
			break;
		case WYVERN_ATTACK::ASSAULT:
			assault_interval = ASSAULT_INTERVAL;
			break;
		case WYVERN_ATTACK::NONE:
			break;
		default:
			break;
		}
		attack_state = WYVERN_ATTACK::NONE;
		attack_end = false;
	}
}

//-----------------------------------
//ブレスの生成
//-----------------------------------
void Wyvern::CreateBless(const Location)
{

}

//-----------------------------------
//強襲攻撃
//-----------------------------------
void Wyvern::Assault(const Location)
{

}

//-----------------------------------
// 攻撃していない
//-----------------------------------
void Wyvern::AttackNone()
{

}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource Wyvern::Hit()
{

}

//-----------------------------------
//死亡
//-----------------------------------
void Wyvern::Death()
{

}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
void Wyvern::HitBullet(const BulletBase* bullet)
{

}

//-----------------------------------
//描画
//-----------------------------------
void Wyvern::Draw() const
{

}

//-----------------------------------
//座標の取得
//-----------------------------------
Location Wyvern::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
//更新(DotByDot)
//-----------------------------------
void Wyvern::Update(const ENEMY_STATE state)
{

}

//-----------------------------------
//描画(DotByDot)
//-----------------------------------
void Wyvern::DebugDraw()
{

}
#endif //_DEBUG