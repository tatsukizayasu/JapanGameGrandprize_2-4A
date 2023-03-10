#include "Harpy.h"
#include "CameraWork.h"

//ハーピィの画像サイズ(未定、画像が出来次第調整）
#define HARPY_SIZE_X 40
#define HARPY_SIZE_Y 80

//プレイヤー発見距離
#define HARPY_DETECTION_DISTANCE 500

//物理攻撃範囲
#define HARPY_ATTACK_RANGE 20

//魔法攻撃範囲	
#define HARPY_ATTACK_MAGIC 400

//魔法攻撃した時の硬直時間
#define HARPY_MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define HARPY_PHYSICAL_STANDBY 100

//ハーピィの攻撃力
#define HARPY_ATTACK_DAMAGE 4

//移動スピード
#define HARPY_SPEED 2.5

//攻撃スピード
#define ATTACK_SPEED 5

//ドロップ量(最小)
#define HARPY_MIN_DROP 0u

//ドロップ量(最大)
#define HARPY_MAX_DROP 4u


//-----------------------------------
// コンストラクタ
//-----------------------------------
Harpy::Harpy()
{
	can_delete = false;
	left_move = true;
	attack = false;

	hp = 10;
	location.x = 1400;
	location.y = 1050;
	standby_attack = 0;
	speed = 1.5;
	area.width = HARPY_SIZE_X;
	area.height = HARPY_SIZE_Y;
	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	inversion = false;
	kind = ENEMY_KIND::GHOST;

	//harpy_image = LoadGraph("Images/Enemy/???????.png"); //画像読込み
	harpy_image = 0; //画像をもらい次第上記の処理に変更

	//ドロップアイテムの設定
	drop_element = new ElementItem * [WIND_DROP];
	drop_type_volume = WIND_DROP;

	int volume = 0;
	for (int i = 0; i < WIND_DROP; i++)
	{
		volume = HARPY_MIN_DROP + GetRand(HARPY_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WIND;
	attack_state = HARPY_ATTACK::NONE;
	state = ENEMY_STATE::IDOL;
	action_type = HARPY_STATE::NORMAL;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
Harpy::~Harpy()
{

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
			speed = 0.1;
		}
		else
		{
			speed = 1.5;
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

	switch (action_type)
	{
	case HARPY_STATE::NORMAL:  //通常移動
		location.x -= speed;
		break;
	case HARPY_STATE::NORMAL_RIGHT://右
		location.x += speed;
		break;
	case HARPY_STATE::LEFT_lOWER:  //左下を目指す
		location.x -= speed;
		location.y += speed;
		break;
	case HARPY_STATE::LEFT_UPPER:  //左上を目指す
		location.x -= speed;
		location.y -= speed;
		break;
	case HARPY_STATE::RIGHT_LOWER:  //右下を目指す
		location.x += speed;
		location.y += speed;
		break;
	case HARPY_STATE::RIGHT_UPPER:  //右上を目指す。
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


	//DrawRotaGraph(draw_location.x, draw_location.y, 1.5f, M_PI / 180, ghost_image, TRUE);
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
		poison_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;
		poison_damage = bullet->GetDamage();
		break;
	case ATTRIBUTE::PARALYSIS: //麻痺 弱点
		paralysis_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;  //弱点
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
Location Harpy::GetLocation() const
{
	return location;
}