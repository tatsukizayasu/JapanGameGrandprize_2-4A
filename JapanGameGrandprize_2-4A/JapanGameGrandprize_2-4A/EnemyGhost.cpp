#include "EnemyGhost.h"
#include"DxLib.h"
#include "CameraWork.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//プレイヤー発見距離
#define GHOST_DETECTION_DISTANCE 500

//物理攻撃範囲
#define GHOST_ATTACK_RANGE 20

//魔法攻撃範囲	
#define GHOST_ATTACK_MAGIC 400

//魔法攻撃した時の硬直時間
#define GHOST_MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define GHOST_PHYSICAL_STANDBY 300

//移動スピード
#define GHOST_SPEED 1.5

//攻撃スピード
#define ATTACK_SPEED 4.5

//ドロップ量(最小)
#define GHOST_MIN_DROP 0u

//ドロップ量(最大)
#define GHOST_MAX_DROP 4u

//ゴーストの攻撃力
#define GHOST_ATTACK_DAMAGE 10

//今日やること
//当たり判定、接近攻撃あれでいいのか

//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	can_delete = false;
	hp = 10;
	location.x = 600;
	location.y = 1200;
	area.width = GHOST_SIZE_X;
	area.height = GHOST_SIZE_Y;
	standby_time = 0;
	standby_count = 0;
	physical_attack = false;
	magic_attack = false;
	kind = ENEMY_KIND::GHOST;

	//ドロップアイテムの設定
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;
	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = GHOST_MIN_DROP + GetRand(GHOST_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = GHOST_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = GHOST_STATE::NORMAL;
	bullet = nullptr;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
EnemyGhost::~EnemyGhost()
{
	delete bullet;
}

//-----------------------------------
// 描画以外の処理
//-----------------------------------
void EnemyGhost::Update()
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
		break;
	case ENEMY_STATE::ATTACK:
		
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}

	if (bullet != nullptr)
	{
		bullet->Update();

		if (bullet->ScreenOut())
		{
			delete bullet;
			bullet = nullptr;
			attack_state = GHOST_ATTACK::NONE;
		}
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}

}

//アイドル状態
void EnemyGhost::Idol()
{

}

//移動
void EnemyGhost::Move(const Location player_location)
{
	GhostMove(player_location);

	switch (action_type)
	{
	case GHOST_STATE::NORMAL:  //通常移動
		location.x -= GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_lOWER:  //左下を目指す
		location.x -= GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::LEFT_UPPER:  //左上を目指す
		location.x -= GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_LOWER:  //右下を目指す
		location.x += GHOST_SPEED;
		location.y += GHOST_SPEED;
		break;
	case GHOST_STATE::RIGHT_UPPER:  //右上を目指す。
		location.x += GHOST_SPEED;
		location.y -= GHOST_SPEED;
		break;
	default:
		break;
	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void  EnemyGhost::Attack(Location player_location)
{
	standby_count++;
	if (standby_time < standby_count)
	{
		switch (attack_state)
		{
		case GHOST_ATTACK::PHYSICAL_ATTACK:
			physical_attack = false;
			attack_state = GHOST_ATTACK::NONE;
			break;
		case GHOST_ATTACK::MAGIC_ATTACK:
			magic_attack = false;
			break;
		case GHOST_ATTACK::NONE:
			break;
		default:
			break;
		}
		standby_time = 0;
		standby_count = 0;
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource EnemyGhost::HitCheck(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	switch (attack_state)
	{
	case GHOST_ATTACK::PHYSICAL_ATTACK:
		if (HitBox(collider))
		{
			ENEMY_TYPE attack_type[1] = { *type };
			ret.damage = GHOST_ATTACK_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
		}
		break;
	case GHOST_ATTACK::MAGIC_ATTACK:
		if (bullet != nullptr)
		{
			if (bullet->HitBox(collider))
			{
				ENEMY_TYPE attack_type[1] = { bullet->GetType() };
				ret.damage = bullet->GetDamage();
				ret.type = attack_type;
				ret.type_count = 1;

				delete bullet;
				bullet = nullptr;
			}
		}
		break;
	case GHOST_ATTACK::NONE:
		break;
	default:
		break;
	}

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void EnemyGhost::Death()
{
	can_delete = true;
}

//-----------------------------------
// 描画
//-----------------------------------
void EnemyGhost::Draw()const
{
	//スクロールに合わせて描画
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	switch (attack_state)
	{
	case GHOST_ATTACK::PHYSICAL_ATTACK:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 0, 0), TRUE);
		break;
	case GHOST_ATTACK::MAGIC_ATTACK:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
		if (bullet != nullptr)
		{
			bullet->Draw();
		}
		break;
	case GHOST_ATTACK::NONE:
		DrawBox(x, y, x + GHOST_SIZE_X, y + GHOST_SIZE_Y, GetColor(255, 255, 0), TRUE);
		break;
	default:
		break;
	}
}


//-----------------------------------
// ゴーストの動き
//-----------------------------------
void EnemyGhost::GhostMove(const Location player_location)
{
	float range; //プレイヤーとの距離	
	
	range = fabsf(location.x - player_location.x);

	//プレイヤーが発見距離内にいたら
	if (range <= GHOST_DETECTION_DISTANCE && range >= -GHOST_DETECTION_DISTANCE)
	{
		if (range > player_location.x) //左に移動
		{
			if (player_location.y > location.y)
			{
				action_type = GHOST_STATE::LEFT_lOWER;
			}
			else 
			{
				action_type = GHOST_STATE::LEFT_UPPER;
			}
		}
		else //右に移動
		{
			if (player_location.y > location.y)
			{
				action_type = GHOST_STATE::RIGHT_LOWER;
			}
			else
			{
				action_type = GHOST_STATE::RIGHT_UPPER;
			}
		}
	}
	else //通常移動
	{
		action_type = GHOST_STATE::NORMAL;
		magic_attack = false;
		physical_attack = false;
	}

	//攻撃範囲内にいる場合
	if ((range <= GHOST_ATTACK_RANGE) && (!physical_attack))
	{
		state = ENEMY_STATE::ATTACK;
		attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
		standby_time = GHOST_PHYSICAL_STANDBY;
		physical_attack = true;
	}
	else if ((range <= GHOST_ATTACK_MAGIC) && (!magic_attack))
	{
		state = ENEMY_STATE::ATTACK;
		attack_state = GHOST_ATTACK::MAGIC_ATTACK;
		standby_time = GHOST_MAGIC_STANDBY;
		magic_attack = true;

		if (bullet == nullptr)
		{
			bullet = new GhostBullet(location, player_location);
		}
	}
}

//-----------------------------------
// プレイヤーの弾丸との当たり判定
//-----------------------------------
bool EnemyGhost::HitBullet(const BulletBase* bullet)
{
	bool ret = false; //戻り値
	if (HitSphere(bullet))
	{
		switch (bullet->GetAttribute()) //受けた化合物の属性
		{
		case ATTRIBUTE::NORMAL: 
			hp -= bullet->GetDamage() * 10; //無効
			break;
	//	case ATTRIBUTE::EXPLOSION:
	//		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE; //弱点属性
	//		break;
	//	case ATTRIBUTE::MELT:
	//		hp -= bullet->GetDamage() * 0; //無効
	//		break;
	//	case ATTRIBUTE::POISON:
	//		poison_damage = bullet->GetDamage() * 0; //無効
	//		poison_time = bullet->GetDebuffTime() * 0; //無効
	//		break;
	//	case ATTRIBUTE::PARALYSIS:
	//		paralysis_time = bullet->GetDebuffTime() * 0; //無効
	//		paralysis_time = bullet->GetDamage() * 0; //無効
	//		break;
	//	case ATTRIBUTE::HEAL:
	//		break;
	//	default:
	//		break;
		}
		ret = true;
	}
	return ret;
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location EnemyGhost::GetLocation() const
{
	return location;
}