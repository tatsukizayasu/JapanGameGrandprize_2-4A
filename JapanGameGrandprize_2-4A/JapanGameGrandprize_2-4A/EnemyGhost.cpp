#include "EnemyGhost.h"
#include"DxLib.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//プレイヤー発見距離
#define DETECTION_DISTANCE 200

//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	ghost_vanish = false;
	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	action_time = 0;
	action_type = GHOST_STATE::NORMAL;
}


//-----------------------------------
// 描画以外の処理
//-----------------------------------
void EnemyGhost::Update()
{

	switch (action_type)
	{
	case GHOST_STATE::NORMAL:  //通常移動
		location.x--;
		break;
	case GHOST_STATE::LEFT_lOWER:  //左下を目指す
		location.x--;
		location.y++;
		break;
	case GHOST_STATE::LEFT_UPPER:  //左上を目指す
		location.x--;
		location.y--;
		break;
	case GHOST_STATE::RIGHT_LOWER:  //右下を目指す
		location.x++;
		location.y++;
		break;
	case GHOST_STATE::RIGHT_UPPER:  //右上を目指す。
		location.x++;
		location.y--;
		break;
	case GHOST_STATE::ATTACK:
		break;
	}


}

//-----------------------------------
// 描画
//-----------------------------------
void EnemyGhost::Draw()const
{
	DrawBox(location.x, location.y, location.x + GHOST_SIZE_X, 
		location.y + GHOST_SIZE_Y,GetColor(255, 0, 0), TRUE);
}


//-----------------------------------
// ゴーストの動き
//-----------------------------------
void EnemyGhost::GhostMove(Player* player)
{
	int range; //プレイヤーとの距離
	range = location.x - player->GetLocationX();

	if (range <= DETECTION_DISTANCE && range >= -DETECTION_DISTANCE)
	{
		if (location.x > player->GetLocationX())
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
		else
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
	else
	{
		action_type = GHOST_STATE::NORMAL;
	}


}


//-----------------------------------
// ゴーストの攻撃処理
//-----------------------------------
void EnemyGhost::GhostAttack()
{

}

//-----------------------------------
// プレイヤーとの距離
//-----------------------------------
bool EnemyGhost::GhostRange()
{
	return true;
}


void EnemyGhost::HitBullet(Bullet* bullet)
{

}