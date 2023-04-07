#include "Dragon.h"
#include "CameraWork.h"
#include"BulletManager.h"
#include "DxLib.h"

//ドラゴンの画像サイズ(未定、画像が出来次第調整）
#define DRAGON_SIZE_X 600
#define DRAGON_SIZE_Y 600

//ドラゴンのHP
#define HIT_POINTS 500

//ドラゴンの移動速度
#define ATTACK_SPEED 30
#define SPEED 15

//魔法攻撃した時の硬直時間
#define MAGIC_STANDBY 60

//近接攻撃した時の硬直時間
#define PHYSICAL_STANDBY 100

//ドラゴンの攻撃力(攻撃別）
//尻尾攻撃
#define ATTACK_TAIL 20

//噛みつく
#define ATTACK_DITE 30 

//接近攻撃の範囲
#define MELEE_ATTACK 150

//攻撃切り替え時間
#define ATTACK_SWITCHOVER 260

//ブレス発射間隔
#define BREATH_INTERVAL 120

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

	hp = HIT_POINTS;
	speed = SPEED;

	animation = 0;
	attack_method = 1;
	animation_time = 0;
	switchover_time = 0;
	effect_time = 0;
	standby_time = 0;
	breath_time = 0;

	can_delete = false;
	left_move = true;
	attack = false;
	magic = false;

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

	image = LoadGraph("Images/Enemy/a.png"); //画像読込み

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

	//毒のダメージ
	if (poison == true)
	{
		if (++effect_time % POISON_DAMAGE_FLAME == 0)
		{
			if (--poison_time > 0)
			{
				hp -= poison_damage;
			}
			else
			{
				poison_damage = 0;
				poison_time = 0;
				poison = false;
			}

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

	/*DrawRotaGraphF(draw_location.x, draw_location.y, 1.4f,
		M_PI / 180, image, TRUE);*/

}

//-----------------------------------
//アイドル状態
//-----------------------------------
void Dragon::Idol()
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
	
	//ランダムで攻撃方法の決定
	if (++switchover_time % ATTACK_SWITCHOVER == 0)
	{
		//HPが半分以下なら雷を落とす攻撃も追加
		if (hp < HIT_POINTS / 2)
		{
			attack_method = GetRand(3);
		}
		else
		{
			attack_method = GetRand(2);
		}
	}

	switch (attack_method)
	{
	case 0:
		attack_state = DRAGON_ATTACK::DITE;
		state = ENEMY_STATE::ATTACK;
		attack = true;
		break;
	case 1:
		attack_state = DRAGON_ATTACK::DREATH;
		state = ENEMY_STATE::ATTACK;
		magic = true;
		break;
	case 2:
		attack_state = DRAGON_ATTACK::TAIL_ATTACK;
		state = ENEMY_STATE::ATTACK;
		break;
	case 3:
		attack_state = DRAGON_ATTACK::ROAR;
		state = ENEMY_STATE::ATTACK;
		magic = true;
		break;
	default:
		break;
	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void Dragon::Attack(const Location player_location)
{

	standby_time--;
	if (standby_time < 0)
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
		standby_time = 0;
	}
}

//-----------------------------------
//接近攻撃時の噛みつき(這いつくばりながら攻撃）体当たりするイメージ
//-----------------------------------
void Dragon::DiteMove(const Location player_location)
{
	//4月7日現在、壁に当たるまで攻撃を続けるのか、
	//攻撃開始直後の座標を目指して移動するのか、

	speed = ATTACK_SPEED;

	if (left_move == true)
	{
		location.x -= speed;
		speed = SPEED;
	}
	else
	{
		location.x += speed;
		speed = SPEED;
	}

}

//-----------------------------------
//尻尾攻撃（地上に降りていたら）
//-----------------------------------
void Dragon::TailMove(const Location player_location)
{
	
}

//-----------------------------------
//遠距離攻撃（ブレス）この時飛びながらブレスを行う
//-----------------------------------
void Dragon::DreathMove(const Location player_location)
{
	if (++breath_time % BREATH_INTERVAL == 0)
	{
		BulletManager::GetInstance()->CreateEnemyBullet
		(new DragonBullet(location, player_location));
		state = ENEMY_STATE::MOVE;
	}
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

	int i = 0;
	int damage = 0;

	for (i = 0; i < LOG_NUM; i++)
	{
		if (!damage_log[i].log)
		{
			break;
		}
	}

	if (LOG_NUM <= i)
	{
		for (i = 0; i < LOG_NUM - 1; i++)
		{
			damage_log[i] = damage_log[i + 1];
		}
		i = LOG_NUM - 1;

	}

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
	damage_log[i].log = true;
	damage_log[i].time = LOG_TIME;
	damage_log[i].damage = damage;
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