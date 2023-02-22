#include "EnemyGhost.h"
#include"DxLib.h"
#include "CameraWork.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//プレイヤー発見距離
#define GHOST_DETECTION_DISTANCE 500

//物理攻撃範囲
#define GHOST_ATTACK_RANGE 15

//魔法攻撃範囲	
#define GHOST_ATTACK_MAGIC 400

//魔法攻撃した時の硬直時間
#define GHOST_MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define GHOST_MAGIC_PHYSICAL 300

//移動スピード
#define GHOST_SPEED 1.5

//攻撃スピード
#define ATTACK_SPEED 4.5

//ゴーストの攻撃力
#define GHOST_ATTACK_DAMAGE 10

//今日やること
//当たり判定、アイテム生成、接近攻撃あれでいいのか

//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	hp = 10;
	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	standby_time = 0;
	standby_count = 0;
	physical_attack = false;
	magic_attack = false;
	kind = ENEMY_KIND::GHOST;
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
		switch (attack_state)
		{
		case GHOST_ATTACK::PHYSICAL_ATTACK:
			standby_count++;
			if (standby_count < GHOST_MAGIC_PHYSICAL) //硬直時間
			{
				physical_attack = true;
				standby_time = 0;
				attack_state = GHOST_ATTACK::NONE;
			}
			break;
		case GHOST_ATTACK::MAGIC_ATTACK:
			standby_count++;
			if (standby_time < GHOST_MAGIC_STANDBY) //硬直時間
			{
				magic_attack = true;
				standby_time = 0;
				attack_state = GHOST_ATTACK::NONE;
			}
			break;
		case GHOST_ATTACK::NONE:
			break;
		default:
			break;
		}
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}

	if (bullet != nullptr)
	{
		bullet->Update();
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
AttackResource EnemyGhost::Attack(const BoxCollider* collider)
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
	int range; //プレイヤーとの距離	
	
	range = location.x - player_location.x;

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
	}

	//攻撃範囲内にいる場合
	if ((range <= GHOST_ATTACK_RANGE) && (range >= -GHOST_ATTACK_RANGE) && (!physical_attack))
	{
		attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
	}
	else if ((range <= GHOST_ATTACK_MAGIC) && (range >= -GHOST_ATTACK_MAGIC) && (!magic_attack))
	{
		attack_state = GHOST_ATTACK::MAGIC_ATTACK;
		if (bullet == nullptr)
		{
			bullet = new GhostBullet(location, player_location);
		}
	}
}

//-----------------------------------
// プレイヤーの弾丸との当たり判定
//-----------------------------------
void EnemyGhost::HitBullet(const BulletBase* bullet)
{

}



