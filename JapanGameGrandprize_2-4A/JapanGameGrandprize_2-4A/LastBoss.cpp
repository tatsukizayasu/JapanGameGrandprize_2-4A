#include "LastBoss.h"
#include "LastBossHand.h"
#include "DxLib.h"
#include "CameraWork.h"

//手の数
#define HAND_NUM 2

//ダウン時の落ちる速度
#define DOWN_MOVE_SPEED 10;

//ダウンしている時間
#define DOWN_TIME 1200

//魔法攻撃
#define MAGIC_TIME 60 * 30

//魔法の発動レート
#define MAGIC_RATE 20

//パンチ攻撃している時間
#define PUNCH_TIME 60 * 20

//攻撃間隔
#define ATTACK_INTERVAL 60 * 1

//次の魔法攻撃までの時間
#define MAGIC_INTERVAL 60 * 10

//次のパンチまでの時間
#define PUNCH_INTERVAL 60 * 10


//次の剣攻撃までの時間
#define SWORD_INTERVAL 60 * 10

//-----------------------------------
//コンストラクタ
//-----------------------------------
LastBoss::LastBoss(Location spawn_location)
{
	Location spawn_hand;
	location = spawn_location;

	spawn_hand = location;
	spawn_hand.x -= 200;

	spawn_hand.y += 100;

	hand = new EnemyBase * [HAND_NUM];

	area.height = 200;
	area.width = 200;

	for (int i = 0; i < HAND_NUM; i++)
	{
		spawn_hand.x += (400 * i);
		hand[i] = new LastBossHand(spawn_hand, static_cast<bool>(i));
	}

	kind = ENEMY_KIND::LAST_BOSS;

	down = false;
	attack = false;
	attack_time = 0;
	down_time = 0;
	attack_interval = ATTACK_INTERVAL;
	magic_interval = 0;
	punch_interval = 0;
	sword_interval = 0;

	animation = 0;
	image_argument = 0;

	state = ENEMY_STATE::ATTACK;
	attack_state = LAST_BOSS_ATTACK::NONE;
	hit_stage = { false,nullptr };

}

//-----------------------------------
//デストラクタ
//-----------------------------------
LastBoss::~LastBoss()
{
	for (int i = 0; i < HAND_NUM; i++)
	{
		delete hand[i];
	}
	delete[] hand;

}

//-----------------------------------
//更新
//-----------------------------------
void LastBoss::Update(const class Player* player, const class Stage* stage)
{
	if (down)
	{
		if (!hit_stage.hit)
		{
			location.y += DOWN_MOVE_SPEED;
		}
		down_time--;
		if (down_time < 0)
		{
			down = false;
		}
	}
	else
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
			Attack(player->GetLocation());
			break;
		case ENEMY_STATE::DEATH:
			break;
		default:
			break;
		}

		for (int i = 0; i < HAND_NUM; i++)
		{
			hand[i]->Update(player, stage);
		}

		if ((hand[0]->GetState() == ENEMY_STATE::DEATH) &&
			(hand[1]->GetState() == ENEMY_STATE::DEATH))
		{
			down = true;
			down_time = DOWN_TIME;
		}

		punch_interval--;
		magic_interval--;
		sword_interval--;
	}
	hit_stage = HitStage(stage);
}

//-----------------------------------
//ダウンからの復帰
//-----------------------------------
bool LastBoss::Revival()
{
	bool ret = false; //戻り値

	return ret;
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void LastBoss::Idol()
{

}

//-----------------------------------
//移動
//-----------------------------------
void LastBoss::Move(const Location player_location)
{

}

//-----------------------------------
//移動時のアニメーション
//-----------------------------------
void LastBoss::MoveAnimation()
{

}

//-----------------------------------
//落下
//-----------------------------------
void LastBoss::Fall()
{

}

//-----------------------------------
//攻撃
//-----------------------------------
void  LastBoss::Attack(const Location)
{
	attack_time--;

	switch (attack_state)
	{
	case LAST_BOSS_ATTACK::MAGIC:
		Magic();
		break;
	case LAST_BOSS_ATTACK::PUNCH:
		Punch();
		break;
	case LAST_BOSS_ATTACK::SWORD:
		Sword();
		break;
	case LAST_BOSS_ATTACK::DEATHBLO:
		break;
	case LAST_BOSS_ATTACK::NONE:
		AttackNone();
		break;
	default:
		break;
	}
}

//-----------------------------------
//魔法攻撃の初期化
//-----------------------------------
void LastBoss::InitMagic()
{
	attack_time = MAGIC_TIME;
}

//-----------------------------------
//魔法攻撃
//-----------------------------------
void LastBoss::Magic()
{
	attack_time--;
	if (attack_time % MAGIC_RATE == 0)
	{

	}
}

//-----------------------------------
//パンチ攻撃の初期化
//-----------------------------------
void LastBoss::InitPunch()
{
	LastBossHand* me_hand;

	attack_state = LAST_BOSS_ATTACK::PUNCH;

	for (int i = 0; i < HAND_NUM; i++)
	{
		me_hand = dynamic_cast<LastBossHand*>(hand[i]);

		me_hand->StartAttack();
	}

	attack_time = PUNCH_TIME;
}

//-----------------------------------
//パンチ攻撃
//-----------------------------------
void LastBoss::Punch()
{
	LastBossHand* me_hand;

	if (attack_time < 0)
	{
		for (int i = 0; i < HAND_NUM; i++)
		{
			me_hand = dynamic_cast<LastBossHand*>(hand[i]);

			me_hand->EndAttack();
		}
		attack_state = LAST_BOSS_ATTACK::NONE;
		punch_interval = PUNCH_INTERVAL;
	}
}

//-----------------------------------
//剣攻撃の初期化
//-----------------------------------
void LastBoss::InitSword()
{

}

//-----------------------------------
//剣攻撃
//-----------------------------------
void LastBoss::Sword()
{


}

//-----------------------------------
//攻撃しない
//-----------------------------------
void LastBoss::AttackNone()
{
	LAST_BOSS_ATTACK next_attack = LAST_BOSS_ATTACK::NONE; //次の攻撃
	int attack_num = 0; //攻撃ができる種類の数
	attack_interval--;
	if (attack_interval < 0) //攻撃可能
	{
		if (magic_interval < 0) //魔法攻撃可能
		{
			attack_num++;
		}

		if (punch_interval < 0) //パンチ攻撃可能
		{
			attack_num++;
		}

		if (sword_interval < 0) //剣攻撃可能
		{
			attack_num++;
		}

		if ((attack_num == 3) || (attack_num == 0)) //攻撃ができる種類の数が3個か0個
		{
			next_attack = static_cast<LAST_BOSS_ATTACK>(GetRand(2));
		}
		else if (attack_num == 2) //攻撃ができる種類の数が2個
		{
			int rand = GetRand(1);

			if ((magic_interval < 0) && (punch_interval < 0)) //魔法攻撃とパンチ攻撃が可能
			{
				next_attack = static_cast<LAST_BOSS_ATTACK>(rand);
			}
			else if((magic_interval < 0) && (sword_interval < 0)) //魔法攻撃と剣攻撃が可能
			{
				next_attack = static_cast<LAST_BOSS_ATTACK>(2 * rand);
			}
			else if ((punch_interval < 0) && (sword_interval < 0)) //パンチ攻撃と剣攻撃が可能
			{
				next_attack = static_cast<LAST_BOSS_ATTACK>(rand + 1);
			}
			else{}
		}
		else if (attack_num == 1) //攻撃ができる種類の数が1個
		{
			if (magic_interval < 0) //魔法攻撃可能
			{
				next_attack = LAST_BOSS_ATTACK::MAGIC;
			}
			else if (punch_interval < 0) //パンチ攻撃可能
			{
				next_attack = LAST_BOSS_ATTACK::PUNCH;
			}
			else if (sword_interval < 0) //剣攻撃可能
			{
				next_attack = LAST_BOSS_ATTACK::SWORD;
			}
			else{}
		}
		else{}

		switch (next_attack) //次の攻撃
		{
		case LAST_BOSS_ATTACK::MAGIC:
			InitMagic();
			break;
		case LAST_BOSS_ATTACK::PUNCH:
			InitPunch();
			break;
		case LAST_BOSS_ATTACK::SWORD:
			InitSword();
			break;
		case LAST_BOSS_ATTACK::DEATHBLO:
		case LAST_BOSS_ATTACK::NONE:
		default:
			break;
		}
	}

		
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource LastBoss::Hit()
{
	AttackResource ret = { 0,nullptr,0 };

	return ret;
}

//-----------------------------------
//プレイヤーとパンチとの当たり判定
//-----------------------------------
AttackResource LastBoss::PunchAttack(const BoxCollider* player)
{
	AttackResource ret = { 0,nullptr,0 };

	LastBossHand* me_hand;
	for (int i = 0; i < HAND_NUM; i++)
	{
		me_hand = dynamic_cast<LastBossHand*>(hand[i]);

		if (me_hand->IfAttack())
		{
			if (me_hand->HitBox(player))
			{
				ret = me_hand->Hit();
			}
		}
	}

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void LastBoss::Death()
{

}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
void LastBoss::HitBullet(const BulletBase* bullet)
{

}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
bool LastBoss::CheckHitBulelt(const BulletBase* bullet)
{
	bool ret = false; //戻り値

	if (down)
	{
		if (HitSphere(bullet))
		{
			ret = true;
			HitBullet(bullet);
		}
	}

	if (!ret)
	{
		for (int i = 0; i < HAND_NUM; i++)
		{
			if (hand[i]->HitSphere(bullet))
			{
				ret = true;
				hand[i]->HitBullet(bullet);
				break;
			}
		}
	}

	return ret;
}

//-----------------------------------
//描画
//-----------------------------------
void LastBoss::Draw() const
{

	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;
	if (down)
	{
		DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
			draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0xffffff, TRUE);
	}
	else
	{
		DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
			draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0x777777, TRUE);
	}

	for (int i = 0; i < HAND_NUM; i++)
	{
		hand[i]->Draw();
	}
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location LastBoss::GetLocation() const
{
	return location;
}

#ifdef _DEBUG
//-----------------------------------
//更新(DotByDot)
//-----------------------------------
void LastBoss::Update(const ENEMY_STATE state)
{

}

//-----------------------------------
//描画(DotByDot)
//-----------------------------------
void LastBoss::DebugDraw()
{

}
#endif //_DEBUG