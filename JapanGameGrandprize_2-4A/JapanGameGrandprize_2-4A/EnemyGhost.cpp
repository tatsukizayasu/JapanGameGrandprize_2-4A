#include "EnemyGhost.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "BulletManager.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 75
#define GHOST_SIZE_Y 80

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
#define GHOST_MIN_DROP 1

//ドロップ量(最大)
#define GHOST_DROP 7

//ゴーストの攻撃力
#define GHOST_ATTACK_DAMAGE 10


//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost(Location spawn_location)
{
	can_delete = false;
	left_move = true;
	attack = false;

	animation = 0;
	animation_time = 0;
	magic_time = 1;
	magic_num = 0;
	physical_time = 0;
	hp = 10;
	location = spawn_location;
	location.y = 120; //テスト
	standby_attack = 0;
	speed = 1.5;
	area.width = GHOST_SIZE_X;
	area.height = GHOST_SIZE_Y;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;

	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	kind = ENEMY_KIND::GHOST;

	LoadDivGraph("Images/Enemy/ghostimages2.png", 5, 5, 1, 75, 80, ghost_image);
	//ドロップアイテムの設定
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;

	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = GHOST_MIN_DROP + GetRand(GHOST_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = GHOST_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = GHOST_STATE::NORMAL;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
EnemyGhost::~EnemyGhost()
{
	delete[] images;
	delete[] type;

	for (int i = 0; i < WIND_DROP; i++)
	{
		delete drop_element[i];
	}
	delete[] drop_element;
}

//-----------------------------------
// 描画以外の処理
//-----------------------------------
void EnemyGhost::Update(const class Player* player, const class Stage* stage)
{
	Location old_location = location;	//前の座標
	HitMapChip hit_stage = { false,nullptr }; //ステージとの当たり判定

	if (animation_time++%5==0)
	{
		animation++;
	}

	if (animation > 4)
	{
		animation = 0;
	}

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());
		
		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
			speed = 0;
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

	hit_stage = HitStage(stage);
	if (hit_stage.hit) //ステージとの当たり判定
	{
		Location chip_location = hit_stage.chip->GetLocation();
		Area chip_area = hit_stage.chip->GetArea();
		if ((chip_location.y + chip_area.height / 2) < (location.y + area.height / 2))
		{
			location = old_location;
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
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		speed = 1.5;
	}
}

//移動
void EnemyGhost::Move(const Location player_location)
{
	GhostMove(player_location);

	switch (action_type)
	{
	case GHOST_STATE::NORMAL:  //通常移動
		location.x -= speed;
		break;
	case GHOST_STATE::NORMAL_RIGHT://右
		location.x += speed;
		break;
	case GHOST_STATE::LEFT_lOWER:  //左下を目指す
		location.x -= speed;
		location.y += speed;
		break;
	case GHOST_STATE::LEFT_UPPER:  //左上を目指す
		location.x -= speed;
		location.y -= speed;
		break;
	case GHOST_STATE::RIGHT_LOWER:  //右下を目指す
		location.x += speed;
		location.y += speed;
		break;
	case GHOST_STATE::RIGHT_UPPER:  //右上を目指す。
		location.x += speed;
		location.y -= speed;
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
	standby_time--;
	if (standby_time < 0)
	{
		switch (attack_state)
		{
		case GHOST_ATTACK::PHYSICAL_ATTACK:
			attack = false;
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
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource EnemyGhost::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (attack_state == GHOST_ATTACK::PHYSICAL_ATTACK && (!attack))
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = GHOST_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
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
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawRotaGraphF(draw_location.x, draw_location.y, 1.5f, M_PI / 180, ghost_image[animation], TRUE);
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
		if (location.x > player_location.x) //左に移動
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
			if (location.y + 10 >= player_location.y && location.y - 10 <= player_location.y)
			{
				action_type = GHOST_STATE::NORMAL_RIGHT;
			}
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

	////攻撃範囲内にいる場合
	//if ((range <= GHOST_ATTACK_RANGE) && (!physical_attack))
	//{
	//	state = ENEMY_STATE::ATTACK;
	//	attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
	//	standby_time = GHOST_PHYSICAL_STANDBY;
	//	physical_attack = true;
	//}
	//else if ((range <= GHOST_ATTACK_MAGIC) && (!magic_attack))
	//{
	//	state = ENEMY_STATE::ATTACK;
	//	attack_state = GHOST_ATTACK::MAGIC_ATTACK;
	//	standby_time = GHOST_MAGIC_STANDBY;
	//	magic_attack = true;
	//	if (magic_time++ % 3 == 0)
	//	{
	//		//弾の生成
	//		BulletManager::GetInstance()->CreateEnemyBullet
	//		(new GhostBullet(location, player_location));
	//	}
	//}
}

//-----------------------------------
//落下
//-----------------------------------
void EnemyGhost::Fall()
{
}

//-----------------------------------
// プレイヤーの弾丸との当たり判定
//-----------------------------------
void EnemyGhost::HitBullet(const BulletBase* bullet)
{
	switch (bullet->GetAttribute()) //受けた化合物の属性
	{
	case ATTRIBUTE::NORMAL:
		hp -= bullet->GetDamage() * 0; //無効
		break;
	case ATTRIBUTE::EXPLOSION:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE; //弱点属性
		break;
	case ATTRIBUTE::MELT:
		hp -= bullet->GetDamage() * 0; //無効
		break;
	case ATTRIBUTE::POISON:
		poison_damage = bullet->GetDamage() * 0; //無効
		poison_time = bullet->GetDebuffTime() * 0; //無効
		break;
	case ATTRIBUTE::PARALYSIS:
		paralysis_time = bullet->GetDebuffTime() * 0; //無効
		paralysis_time = bullet->GetDamage() * 0; //無効
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
Location EnemyGhost::GetLocation() const
{
	return location;
}