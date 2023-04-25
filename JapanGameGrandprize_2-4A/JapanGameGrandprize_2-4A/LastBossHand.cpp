#include "LastBossHand.h"
#include "Player.h"
#include "Stage/Stage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CameraWork.h"

#define HAND_IMAGES

//移動速度
#define HAND_MOVE_SPEED 2

//次のパンチまでの時間
#define PUNCH_INTERVAL 300

//パンチするまでの時間
#define PUNCH_STANDBY_TIME 60 

//パンチのスピード
#define PUNCH_SPEED 8

//パンチのダメージ
#define PUNCH_DAMAGE 15

//HP
#define HAND_HP 100

//死亡している時間
#define DEATH_TIME 1200

//移動量
#define MOVE_VOLUME 100

//角度の上昇量
#define ADD_ANGLE 2

//半径の上昇量
#define ADD_RADIUS 1

//移動半径
#define MOVE_RADIUS 50
//-----------------------------------
//コンストラクタ
//-----------------------------------
LastBossHand::LastBossHand(const Location spawn_location, const bool left_hand)
{
	this->spawn_location = spawn_location;
	location = spawn_location;
	punch_start = location;

	area.height = 100;
	area.width = 100;

	punch = false;
	attack = false;

	move_volume = 0;
	angle = 0;
	radius = 0;
	attack_interval = 0;
	punch_standby_time = 0;
	animation = 0; 
	image_argument = 0;

	can_delete = false;
	this->left_hand = left_hand;
	left_move = false;
	poison = false;
	paralysis = false;

	damage = 0;
	images = nullptr;
	hp = HAND_HP;
	speed = -HAND_MOVE_SPEED;
	death_time = 0;
	poison_time = 0;
	poison_damage = 0;
	paralysis_time = 0;
	drop_volume = 0;
	drop_type_volume = 0;
	drop_element = nullptr;

	kind = ENEMY_KIND::LAST_BOSS;
	type = new ENEMY_TYPE[1];
	state = ENEMY_STATE::ATTACK;

	move = HAND_MOVE::UP_DOWN;

	hit_block.chip = nullptr;
	hit_block.hit = false;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
LastBossHand::~LastBossHand()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

	/*for (int i = 0; i < HAND_IMAGES; i++)
	{
		DeleteGraph(images[i]);
	}

	delete[] images;*/
}

//-----------------------------------
//更新
//-----------------------------------
void LastBossHand::Update(const Player* player, const Stage* stage)
{
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

	hit_block = HitStage(stage);

	attack_interval--;

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;

		location.x = -100;
		location.y = -100;
		death_time = DEATH_TIME;
	}

	UpdateDamageLog();
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void LastBossHand::Idol()
{

}

//-----------------------------------
//移動
//-----------------------------------
void LastBossHand::Move(const Location player_location)
{

	switch (move)
	{
	case HAND_MOVE::UP_DOWN:
	{
		location.y += speed;
		move_volume += speed;

		if ((move_volume < -MOVE_VOLUME) || ((MOVE_VOLUME /4) < move_volume))
		{
			speed = -speed;
		}
	}
		break;
	case HAND_MOVE::CIRCULAR_MOTION:
	{
		Location circular_speed; //スピード
		float radian = 0; //角度

		if (left_hand)		//角度の設定
		{
			angle += ADD_ANGLE;
		}
		else
		{
			angle += -ADD_ANGLE;
		}

		if (radius < MOVE_RADIUS) //半径
		{
			radius += ADD_RADIUS;
		}

		//角度の計算
		radian = angle * (M_PI / 180);

		//スピードの計算
		circular_speed.x = cosf(radian);
		circular_speed.y = sinf(radian);

		location.x = spawn_location.x + (circular_speed.x * radius);
		location.y = spawn_location.y + (circular_speed.y * radius);
	}
		break;
	case HAND_MOVE::NONE:
	default:
		break;
	}
	
}

//-----------------------------------
//落下
//-----------------------------------
void LastBossHand::Fall()
{

}

//-----------------------------------
//攻撃
//-----------------------------------
void LastBossHand::Attack(const Location player_location)
{
	bool old_punch = punch;

	if (punch) //パンチしている
	{
		Punch();
	}
	else
	{
		location.x = player_location.x;
		punch = true;
		speed = PUNCH_SPEED;
	}

	if (old_punch && (old_punch != punch)) //パンチ終了
	{
		location = spawn_location;
		state = ENEMY_STATE::MOVE;
		move = static_cast<HAND_MOVE>(GetRand(2));
		speed = HAND_MOVE_SPEED;
		attack_interval = PUNCH_INTERVAL;
		attack = false;
	}
}

//-----------------------------------
//パンチ
//-----------------------------------
void LastBossHand::Punch()
{
	if (punch_standby_time < 0)
	{
		location.y += speed;
		if (hit_block.hit)
		{
			speed = -PUNCH_SPEED;
			attack = false;
		}

		if (location.y <= punch_start.y )
		{
			punch = false;
		}
	}
	else
	{
		punch_standby_time--;
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource LastBossHand::Hit()
{
	AttackResource ret = { 0,nullptr,0 };
	ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::NORMAL };

	if (punch && attack)
	{
		ret.damage = PUNCH_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
	}
	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void LastBossHand::Death()
{
	death_time--;

	if (death_time < 0)
	{
		state = ENEMY_STATE::MOVE;
		location = spawn_location;
		hp = HAND_HP;

		move = static_cast<HAND_MOVE>(GetRand(2));
	}
}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
void LastBossHand::HitBullet(const BulletBase* bullet)
{

	int i;
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

	switch (bullet->GetAttribute())
	{
	case ATTRIBUTE::NORMAL:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::EXPLOSION:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::MELT:
		damage = bullet->GetDamage();
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
		break;
	case ATTRIBUTE::POISON:
	case ATTRIBUTE::PARALYSIS:
	case ATTRIBUTE::HEAL:
	default:
		break;
	}

	damage_log[i].log = true;
	damage_log[i].time = LOG_TIME;
	damage_log[i].damage = damage;
	hp -= damage;

}

//-----------------------------------
//移動時のアニメーション
//-----------------------------------
void LastBossHand::MoveAnimation()
{

}

//-----------------------------------
//描画
//-----------------------------------
void LastBossHand::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	if (state != ENEMY_STATE::DEATH)
	{
		draw_location = draw_location - camera;

		DrawHPBar(HAND_HP);

		DrawDamageLog();

		DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
			draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0xffffff, TRUE);

	}

}

//-----------------------------------
//HPバーの表示
//-----------------------------------
void LastBossHand::DrawHPBar(const int)const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();

	int bar_size = 50;

	draw_location = draw_location - camera;

	DrawBox(draw_location.x - bar_size, draw_location.y - 80,
		draw_location.x + bar_size, draw_location.y - 70, 0x000000, TRUE);

	DrawBox(draw_location.x - bar_size, draw_location.y - 80,
		draw_location.x - bar_size + ((bar_size * 2) * (static_cast<float>(hp) / HAND_HP)),
		draw_location.y - 70, 0x07ff00, TRUE);

	DrawBox(draw_location.x - bar_size, draw_location.y - 80,
		draw_location.x + bar_size, draw_location.y - 70, 0x8f917f, FALSE);
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location LastBossHand::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
//更新(DotByDot)
//-----------------------------------
void LastBossHand::Update(const ENEMY_STATE state)
{

}

//-----------------------------------
//描画(DotByDot)
//-----------------------------------
void LastBossHand::DebugDraw()
{

}
#endif //_DEBUG