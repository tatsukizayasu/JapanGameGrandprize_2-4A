#include "EnemyGhost.h"
#include"DxLib.h"

//ゴーストの画像サイズ
#define GHOST_SIZE_X 40
#define GHOST_SIZE_Y 60

//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	ghost_death = false;
	ghost_vanish = false;  
	location.x = 600;
	location.y = 300;
	area.height = 40;
	area.width = 40;
	action_time = 0;
	action_type = 0;
}


//-----------------------------------
// 描画以外の処理
//-----------------------------------
void EnemyGhost::Update()
{
	switch (action_type)
	{
	case 1:
		location.x--;
		break;
	case 2:
		location.x++;
		break;
	

	}
	

}

//-----------------------------------
// 描画
//-----------------------------------
void EnemyGhost::Draw()const
{
	DrawFormatString(60, 60, GetColor(255, 0, 0), "%d", action_time);
	DrawBox(location.x, location.y, location.x + GHOST_SIZE_X, location.y + GHOST_SIZE_Y, GetColor(255,0,0), TRUE);
}


//-----------------------------------
// ゴーストの動き
//-----------------------------------
void EnemyGhost::GhostMove(Player*player)
{
	int range; //プレイヤーとの距離
	action_time= location.x - player->GetLocationX();
	range = location.x - player->GetLocationX();
	if (range <= 100)
	{
		if (location.x> player->GetLocationX())
		{
			action_type = 1;
		}
		else
		{
			action_type = 2;
		}
	}
	else
	{
		action_type = 0;
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