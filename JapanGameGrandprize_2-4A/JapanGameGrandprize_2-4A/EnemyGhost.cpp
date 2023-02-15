#include "EnemyGhost.h"
#include"DxLib.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//プレイヤー発見距離
#define DETECTION_DISTANCE 500

//物理攻撃範囲
#define ATTACK_RANGE 100

//魔法攻撃範囲	
#define ATTACK_MAGIC 400

//移動スピード
#define GHOST_SPEED 1.5

//攻撃スピード
#define ATTACK_SPEED 4.5


//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost()
{

	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	standby_time = 0;
	physical_attack = false;
	magic_attack = false;
	ghost_vanish = false;
	action_type = GHOST_STATE::NORMAL;
	kind = ENEMY_KIND::GHOST;
}


//-----------------------------------
// 描画以外の処理
//-----------------------------------
void EnemyGhost::Update()
{

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
	case GHOST_STATE::MAGIC_ATTACK: //魔法攻撃
		if (standby_time++ % 600 == 0)
		{
			magic_attack = true;
		}
		break;
	case GHOST_STATE::PHYSICAL_ATTACK:
		physical_attack = true;
		break;
	}

	GhostAttack(); //

}

//-----------------------------------
// 描画
//-----------------------------------
void EnemyGhost::Draw()const
{

	if (action_type == GHOST_STATE::MAGIC_ATTACK) //魔法攻撃のモーション
	{
		DrawBox(location.x, location.y, location.x + GHOST_SIZE_X,
			location.y + GHOST_SIZE_Y, GetColor(0, 255, 0), TRUE);
	}
	else if (action_type == GHOST_STATE::PHYSICAL_ATTACK) //接近攻撃のモーション
	{
		DrawBox(location.x, location.y, location.x + GHOST_SIZE_X,
			location.y + GHOST_SIZE_Y, GetColor(255, 0, 0), TRUE);
	}
	else
	{
		DrawBox(location.x, location.y, location.x + GHOST_SIZE_X,
			location.y + GHOST_SIZE_Y, GetColor(255, 0, 255), TRUE);
	}


}


//-----------------------------------
// ゴーストの動き
//-----------------------------------
void EnemyGhost::GhostMove(Player* player)
{
	int range; //プレイヤーとの距離
	range = location.x - player->GetLocationX();

	//プレイヤーが発見距離内にいたら
	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE)
	{
		if (location.x > player->GetLocationX()) //左に移動
		{
			if (player->GetLocationY() > location.y)
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
			if (player->GetLocationY() > location.y)
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
	if (range <= ATTACK_RANGE && range >= -ATTACK_RANGE && physical_attack == false)
	{
		action_type = GHOST_STATE::PHYSICAL_ATTACK;
	}
	else if (range <= ATTACK_MAGIC && range >= -ATTACK_MAGIC && magic_attack == false)
	{
		action_type = GHOST_STATE::MAGIC_ATTACK;
	}
}


//-----------------------------------
// ゴーストの攻撃処理
//-----------------------------------
void EnemyGhost::GhostAttack()
{
	if (magic_attack == true) //魔法攻撃
	{

	}

	if (physical_attack == true) //物理攻撃
	{

	}
}

void EnemyGhost::HitBullet(Bullet* bullet)
{

}