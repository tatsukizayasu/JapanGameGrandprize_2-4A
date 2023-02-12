#include "EnemyGhost.h"
#include"DxLib.h"

//ゴーストの画像サイズ
#define GHOST_SIZE 20

//-----------------------------------
// コンストラクタ
//-----------------------------------
EnemyGhost::EnemyGhost()
{
	ghost_death = false;
	ghost_vanish = false;  
	ghost_x = 600;
	ghost_y = 400;
	action_time = 0;
	action_type = 0;
	action_type = 0;

}


//-----------------------------------
// 描画以外の処理
//-----------------------------------
void EnemyGhost::Update()
{

	GhostMove();
	GhostAttack();

}

//-----------------------------------
// 描画
//-----------------------------------
void EnemyGhost::Draw()const
{
	DrawBox(ghost_x, ghost_y, ghost_x + GHOST_SIZE, ghost_y + GHOST_SIZE, 0x00ff00, TRUE);
}


//-----------------------------------
// ゴーストの動き
//-----------------------------------
void EnemyGhost::GhostMove()
{

	if (action_time++ % 120 == 0) {
		action_type = GetRand(3);
	}
	switch (action_type)
	{
	case 0:
		ghost_x++;
		ghost_y--;
		break;
	case 1:
		ghost_x--;
		ghost_y++;
		break;
	case 2:
		ghost_x++;
		break;
	case 3:
		ghost_x--;
		break;
	}

}


//-----------------------------------
// ゴーストの攻撃処理
//-----------------------------------
void EnemyGhost::GhostAttack()
{



}