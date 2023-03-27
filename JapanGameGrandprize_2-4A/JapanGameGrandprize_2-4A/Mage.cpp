#include "Mage.h"
#include "CameraWork.h"
#include "MageBullet.h"
#include "BulletManager.h"

//魔法弾の発射レート
#define MAGE_SHOT_RATE 40

//移動速度
#define MAGE_SPEED 2

//ドロップ数
#define MAGE_MIN_DROP 1
#define MAGE_DROP 8

//体力
#define MAGE_HP 100

//移動範囲(直径)
#define MAGE_TELEPORT_AREA 600
#define MAGE_TELEPORT_RATE 160

//麻痺状態の処理
#define MAGE_PARALYSIS_RATE 1.5f

//攻撃間隔
#define MAGE_ATTACK_INTERVAL 240

//-----------------------------------
//コンストラクタ
//-----------------------------------
Mage::Mage(Location spawn_location)
{
	/*初期化*/
	can_delete = false;
	can_teleport = true;
	left_move = true;
	hp = MAGE_HP;
	shot_rate = 0;
	shot_count = 0;
	teleport_count = 0;
	teleport_rate = 0;
	attack_interval = 0;
	speed = MAGE_SPEED;
	kind = ENEMY_KIND::MAGE;
	type = new ENEMY_TYPE[1];
	
	type[0] = static_cast<ENEMY_TYPE>(1 + GetRand(3));
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;

	/*当たり判定の設定*/
	location = spawn_location;
	area.width = 40;
	area.height = 80;

	location.x -= MAP_CHIP_SIZE / 2;
	location.y -= MAP_CHIP_SIZE / 2;
	//ドロップアイテムの設定
	drop = 0;

	switch (type[0])
	{
	case ENEMY_TYPE::NORMAL:
		break;
	case ENEMY_TYPE::FIRE:
		drop = FIRE_DROP;
		image = 0xff0000;
		break;
	case ENEMY_TYPE::WATER:
		drop = WATER_DROP;
		image = 0x0000ff;
		break;
	case ENEMY_TYPE::WIND:
		drop = WIND_DROP;
		image = 0xffffff;
		break;
	case ENEMY_TYPE::SOIL:
		drop = SOIL_DROP;
		image = 0xffff00;
		break;
	case ENEMY_TYPE::THUNDER:
		break;
	default:
		break;
	}

	drop_element = new ElementItem * [drop];
	drop_type_volume = drop;

	int volume = 0;

	for (int i = 0; i < drop; i++)
	{

		volume = MAGE_MIN_DROP + GetRand(MAGE_DROP);

		switch (type[0])
		{
		case ENEMY_TYPE::NORMAL:
			break;
		case ENEMY_TYPE::FIRE:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			break;
		case ENEMY_TYPE::WATER:
			if (i < 2)
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			}
			else
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			}
			break;
		case ENEMY_TYPE::WIND:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			break;
		case ENEMY_TYPE::SOIL:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			break;
		case ENEMY_TYPE::THUNDER:
			break;
		default:
			break;
		}

		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}
}

//-----------------------------------
//デストラクタ
//-----------------------------------
Mage::~Mage()
{
	delete[] type;

	for (int i = 0; i < drop; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;
}

//-----------------------------------
//更新
//-----------------------------------
void Mage::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//前の座標

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:

		Move(player->GetLocation());

		if (can_teleport)
		{
			Teleport(stage);
		}

		if (ScreenOut())
		{
			state = ENEMY_STATE::IDOL;
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

	if (CheckHp() && (state != ENEMY_STATE::DEATH))
	{
		state = ENEMY_STATE::DEATH;
	}
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void Mage::Idol()
{
	if (!ScreenOut())
	{
		state = ENEMY_STATE::MOVE;
		if (paralysis)
		{
			teleport_rate = MAGE_TELEPORT_RATE * MAGE_PARALYSIS_RATE;
		}
		else
		{
			teleport_rate = MAGE_TELEPORT_RATE;
		}
	}
}

//-----------------------------------
//移動
//-----------------------------------
void Mage::Move(const Location player_location)
{
	teleport_count++;
	attack_interval--;

	if (teleport_count % teleport_rate == 0) //テレポートする
	{
		can_teleport = true;
	}

	if (attack_interval < 0) //攻撃に移行
	{
		state = ENEMY_STATE::ATTACK;
	}
}

//-----------------------------------
//テレポート
//-----------------------------------
void Mage::Teleport(const Stage* stage)
{
	HitMapChip hit_stage;

	float radian; //角度
	int teleport; //テレポートの場所距離
	Location old_location = location; //元の地点

	Location camera = CameraWork::GetCamera();

	while (true)
	{
		//テレポートする距離設定
		teleport = (MAGE_TELEPORT_AREA / 2) - GetRand(MAGE_TELEPORT_AREA);
		//角度の計算
		radian = GetRand(360) * (M_PI / 180);

		//テレポートの座標の計算
		location.x = old_location.x + (teleport * cosf(radian));
		location.y = old_location.y + (teleport * sinf(radian));

		Location scroll = location; //画面スクロールを考慮した座標
		//画面スクロールを考慮した座標の計算
		scroll = scroll - camera;

		//ステージとの当たり判定の取得
		hit_stage = HitStage(stage);

		if ((-area.width < scroll.x) && (scroll.x < SCREEN_WIDTH + area.width) &&
			(-area.height < scroll.y) && (scroll.y < SCREEN_HEIGHT + area.height))
		{
			if (!hit_stage.hit)
			{
				break;
			}
		}
	}
	can_teleport = false;
}

//-----------------------------------
//落下
//-----------------------------------
void Mage::Fall()
{
}

//-----------------------------------
//攻撃
//-----------------------------------
void  Mage::Attack(Location player_location)
{
	CreateBullet(player_location);
	
	if (shot_count >= MAGE_BULLET_MAX)
	{
		state = ENEMY_STATE::MOVE;
		shot_count = 0;
		teleport_count = 0;

		if (paralysis)
		{
			teleport_rate = MAGE_TELEPORT_RATE * MAGE_PARALYSIS_RATE;
			attack_interval = MAGE_ATTACK_INTERVAL * MAGE_PARALYSIS_RATE;
		}
		else
		{
			teleport_rate = MAGE_TELEPORT_RATE;
			attack_interval = MAGE_ATTACK_INTERVAL;
		}
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource Mage::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void Mage::Death()
{
	can_delete = true;
}

//-----------------------------------
//弾の生成
//-----------------------------------
void Mage::CreateBullet(Location player_location)
{
	shot_rate++;

	if (shot_rate % MAGE_SHOT_RATE == 0)
	{
		BulletManager::GetInstance()->CreateEnemyBullet
		(new MageBullet(type[0], location, player_location));

		shot_count++;
	}
}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
void Mage::HitBullet(const BulletBase* bullet)
{
	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
		break;
	case ATTRIBUTE::EXPLOSION:
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
		break;
	case ATTRIBUTE::MELT:
		hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
		break;
	case ATTRIBUTE::POISON:
		if (!poison)
		{
			poison = true;
			poison_damage = bullet->GetDamage();
			poison_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		if (!paralysis)
		{
			paralysis = true;
			paralysis_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
		}
		break;
	case ATTRIBUTE::HEAL:
		break;
	default:
		break;
	}
}

//-----------------------------------
//描画
//-----------------------------------
void Mage::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2, image, TRUE);
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location Mage::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
// 更新(DotByDot)
//-----------------------------------
void Mage::Update(const ENEMY_STATE state)
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
void Mage::DebugDraw()
{
	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		0xffffff, FALSE);
}
#endif //_DEBUG