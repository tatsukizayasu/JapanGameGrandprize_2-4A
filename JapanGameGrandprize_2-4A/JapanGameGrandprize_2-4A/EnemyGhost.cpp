#include "EnemyGhost.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "BulletManager.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 60
#define GHOST_SIZE_Y 66

//プレイヤー発見距離
#define DETECTION_DISTANCE 500
#define DETECTION_DISTANCE_Y 300

//物理攻撃範囲
#define ATTACK_RANGE 100
#define ATTACK_RANGE_Y 100

//魔法攻撃した時の硬直時間
#define MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define PHYSICAL_STANDBY 100

//移動スピード
#define SPEED 1.5

//攻撃スピード
#define ATTACK_SPEED 4.5

//ドロップ量(最小)
#define GHOST_MIN_DROP 1

//ドロップ量(最大)
#define GHOST_DROP 7

//ゴーストの攻撃力
#define ATTACK_DAMAGE 10

//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost(Location spawn_location)
{

	can_delete = false;
	left_move = true;
	attack = false;

	vector = 0;
	travel = 0;
	travel_y = 0;
	range = 0;
	range_y = 0;
	animation = 0;
	animation_time = 0;
	magic_time = 1;
	magic_num = 0;
	physical_time = 0;
	hp = 10;
	location = spawn_location;
	//location.y = 250; //テスト
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

	images = new int[7];
	LoadDivGraph("Images/Enemy/ghostman3.png", 6, 6, 1, 60, 66, images);
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


	//アニメーションゴースト
	if (animation_time++ % 10 == 0)
	{
		animation++;
	}

	if (animation > 5)
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
		AttackMove(player->GetLocation());
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

	//プレイヤーとの距離計算
	range = player_location.x - location.x;
	range_y = player_location.y - location.y;

	vector = sqrt(range * range + range_y * range_y);


	//プレイヤーが発見距離内にいたら
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE
		&& range <= DETECTION_DISTANCE_Y && range >= -DETECTION_DISTANCE_Y)
	{

		if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE
			&& range <= ATTACK_RANGE && range >= -ATTACK_RANGE)
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = GHOST_ATTACK::PHYSICAL_ATTACK;
			standby_time = PHYSICAL_STANDBY;
			physical_attack = true;

		}
		else
		{
			state = ENEMY_STATE::ATTACK;
			attack_state = GHOST_ATTACK::MAGIC_ATTACK;
			standby_time = MAGIC_STANDBY;
			magic_attack = true;
			if (magic_time++ % 2 == 0)
			{
				//弾の生成
				BulletManager::GetInstance()->CreateEnemyBullet
				(new GhostBullet(location, player_location));
			}
		}
	}

	else //通常移動
	{
		magic_attack = false;
		physical_attack = false;
		switch (action_type)
		{
		case GHOST_STATE::NORMAL:  //通常移動
			location.x -= speed;
			break;
		case GHOST_STATE::NORMAL_RIGHT://右
			location.x += speed;
			break;
		default:
			break;
		}
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
		ret.damage = ATTACK_DAMAGE;
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


	DrawRotaGraphF(draw_location.x, draw_location.y, 1.4f,
		M_PI / 180, images[animation], TRUE);
}

//-----------------------------------
// 接近攻撃
//-----------------------------------
void EnemyGhost::AttackMove(const Location player_location)
{
	
	if (physical_attack == true)
	{
		range = player_location.x - location.x;
		range_y = player_location.y - location.y;

		vector = sqrt(range * range + range_y * range_y);

		travel = range / vector;
		travel_y = range_y / vector;
		location.x += travel * speed;
		location.y += travel_y * speed;
	}
	
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

#ifdef _DEBUG
//-----------------------------------
// 更新(DotByDot)
//-----------------------------------
void EnemyGhost::Update(const ENEMY_STATE state)
{
	
	switch (state)
	{
	case ENEMY_STATE::IDOL:
		break;
	case ENEMY_STATE::MOVE:
		//アニメーションゴースト
		if (animation_time++ % 10 == 0)
		{
			animation++;
		}

		if (animation > 5)
		{
			animation = 0;
		}
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
void EnemyGhost::DebugDraw()
{
	DrawRotaGraphF(location.x, location.y, 1.5f, M_PI / 180, images[animation], TRUE);

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xffffff, FALSE);
}
#endif //_DEBUG