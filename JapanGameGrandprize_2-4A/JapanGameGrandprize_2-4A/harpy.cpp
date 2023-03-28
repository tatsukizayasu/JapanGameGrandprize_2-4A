#include "Harpy.h"
#include "CameraWork.h"
#include "BulletManager.h"
#include "DxLib.h"

//ハーピィの画像サイズ(未定、画像が出来次第調整）
#define HARPY_SIZE_X 40
#define HARPY_SIZE_Y 80

//プレイヤー発見距離
#define DETECTION_DISTANCE 600
#define DETECTION_DISTANCE_Y 250

//攻撃範囲
#define ATTACK_RANGE 150

//魔法攻撃した時の硬直時間
#define MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define PHYSICAL_STANDBY 100

//ハーピィの攻撃力
#define HARPY_ATTACK_DAMAGE 4

//移動スピード
#define SPEED 2.5

//攻撃スピード
#define ATTACK_SPEED 5

//ドロップ量(最小)
#define HARPY_MIN_DROP 1

//ドロップ量(最大)
#define HARPY_DROP 6

//-----------------------------------
// コンストラクタ
//-----------------------------------
Harpy::Harpy(Location spawn_location)
{

	can_delete = false;
	left_move = true;
	attack = false;

	hp = 50;
	physical_time = 0;
	magic_num = 0;
	magic_time = 1;
	location = spawn_location;
	standby_attack = 0;
	travel = 0;
	travel_y = 0;
	range = 0;
	range_y = 0;
	vector = 0;
	speed = SPEED;
	area.width = HARPY_SIZE_X;
	area.height = HARPY_SIZE_Y;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;

	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	inversion = false;
	kind = ENEMY_KIND::HARPY;

	//harpy_image = LoadGraph("Images/Enemy/???????.png"); //画像読込み
	harpy_image = 0; //画像をもらい次第上記の処理に変更

	//ドロップアイテムの設定
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;
	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = HARPY_MIN_DROP + GetRand(HARPY_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::WIND;
	attack_state = HARPY_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = HARPY_STATE::NORMAL;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
Harpy::~Harpy()
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
void Harpy::Update(const class Player* player, const class Stage* stage)
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
		if (physical_attack == true)
		{
			PhysicalMove(player->GetLocation());
		}
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
			//速度を落とすかもしくは、反転させる処理を作成
			location = old_location;
			/*if (left_move ==true)
			{
				left_move = false;
			}
			else
			{
				left_move = false;
			}*/
		}

	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
	}
}

//アイドル状態
void Harpy::Idol()
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

//移動
void Harpy::Move(const Location player_location)
{

	//プレイヤーとの距離計算
	range = player_location.x - location.x;
	range_y = player_location.y - location.y;


	//プレイヤーが発見距離内にいたら
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE &&
		range_y <= DETECTION_DISTANCE_Y && range_y >= -DETECTION_DISTANCE_Y)
	{
		//接近攻撃
		if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE || magic_num > 4)
		{

			state = ENEMY_STATE::ATTACK;
			attack_state = HARPY_ATTACK::PHYSICAL_ATTACK;
			standby_time = PHYSICAL_STANDBY;
			physical_attack = true;

		}
		//遠距離攻撃
		else
		{

			state = ENEMY_STATE::ATTACK;
			attack_state = HARPY_ATTACK::MAGIC_ATTACK;
			standby_time = MAGIC_STANDBY;
			magic_attack = true;

			//発射間隔
			if (magic_time++ % 2 == 0)
			{
				//弾の生成
				magic_num++;
				BulletManager::GetInstance()->CreateEnemyBullet
				(new HarpyBullet(location, player_location));
			}
		}
	}
	else //発見距離にプレイヤーがいなかったら。通常移動
	{
		if (left_move == true)
		{
			action_type = HARPY_STATE::NORMAL; //左
		}
		else
		{
			action_type = HARPY_STATE::NORMAL_RIGHT; //右
		}
		switch (action_type)
		{
		case HARPY_STATE::NORMAL:  //通常移動
			location.x -= speed;
			break;
		case HARPY_STATE::NORMAL_RIGHT://右
			location.x += speed;
			break;
		case HARPY_STATE::NONE:
			break;
		default:
			break;
		}
	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void  Harpy::Attack(Location player_location)
{

	standby_time--;
	if (standby_time < 0)
	{
		switch (attack_state)
		{
		case HARPY_ATTACK::PHYSICAL_ATTACK:
			attack = false;
			physical_attack = false;
			attack_state = HARPY_ATTACK::NONE;
			break;
		case HARPY_ATTACK::MAGIC_ATTACK:
			magic_attack = false;
			break;
		case HARPY_ATTACK::NONE:
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
AttackResource Harpy::Hit()
{

	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (attack_state == HARPY_ATTACK::PHYSICAL_ATTACK && (!attack))
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = HARPY_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void Harpy::Death()
{

	can_delete = true;
}

//-----------------------------------
// 描画
//-----------------------------------
void Harpy::Draw()const
{

	//スクロールに合わせて描画
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);
}

//-----------------------------------
//落下
//-----------------------------------
void Harpy::Fall()
{

}

//-----------------------------------
// プレイヤーの弾丸との当たり判定
//-----------------------------------
void Harpy::HitBullet(const BulletBase* bullet)
{

	switch (bullet->GetAttribute()) //受けた化合物の属性
	{
	case ATTRIBUTE::NORMAL: //通常弾 
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE; //効きにくい
		break;
	case ATTRIBUTE::EXPLOSION: //爆発 
		hp -= bullet->GetDamage(); //通常
		break;
	case ATTRIBUTE::MELT: //溶かす 
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE; //効きにくい
		break;
	case ATTRIBUTE::POISON: //毒　弱点
		if (!poison)
		{
			poison = true;
			poison_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;
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
//接近攻撃（物理攻撃）時の動き
//-----------------------------------
void Harpy::PhysicalMove(const Location player_location)
{

	range = player_location.x - location.x;
	range_y = player_location.y - location.y;

	vector = sqrt(range * range + range_y * range_y);

	travel = range / vector;
	travel_y = range_y / vector;
	location.x += travel * speed;
	location.y += travel_y * speed;

	if (physical_time++ % 5 == 0)
	{
		magic_num = 0;
	}
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location Harpy::GetLocation() const
{

	return location;
}

#ifdef _DEBUG
//-----------------------------------
// 更新(DotByDot)
//-----------------------------------
void Harpy::Update(const ENEMY_STATE state)
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
void Harpy::DebugDraw()
{
	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xffffff, FALSE);
}
#endif //_DEBUG