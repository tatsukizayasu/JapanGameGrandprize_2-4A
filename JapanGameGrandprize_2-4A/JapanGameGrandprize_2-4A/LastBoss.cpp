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

//パンチしている時間
#define PUNCH_TIME 60 * 60

//攻撃間隔
#define ATTACK_INTERVAL 60 * 1

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
	down_time = 0;
	attack_interval = ATTACK_INTERVAL;

	state = ENEMY_STATE::ATTACK;
	attack_state = LAST_BOSS_ATTACK::NONE;
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
	switch (attack_state)
	{
	case LAST_BOSS_ATTACK::MAGIC:
		break;
	case LAST_BOSS_ATTACK::PUNCH:
		Punch();
		break;
	case LAST_BOSS_ATTACK::SWORD:
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
//パンチ処理
//-----------------------------------
void LastBoss::Punch()
{
	
}

//攻撃しない
void LastBoss::AttackNone()
{
	attack_interval--;
	if (attack_interval < 0)
	{
		LAST_BOSS_ATTACK next_attack = LAST_BOSS_ATTACK::PUNCH;

		switch (next_attack)
		{
		case LAST_BOSS_ATTACK::MAGIC:
			break;
		case LAST_BOSS_ATTACK::PUNCH:
		{
			LastBossHand* me_hand;

			attack_state = LAST_BOSS_ATTACK::PUNCH;

			for (int i = 0; i < HAND_NUM; i++)
			{
				me_hand = dynamic_cast<LastBossHand*>(hand[i]);

				me_hand->StartAttack();
			}
		}
			break;
		case LAST_BOSS_ATTACK::SWORD:
			break;
		case LAST_BOSS_ATTACK::DEATHBLO:
			break;
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