#include "EnemyGhost.h"
#include"DxLib.h"

EnemyGhost::EnemyGhost()
{
	ghost_lost = false;
	ghost_hide = false;
	ghost_x = 600;
	ghost_y = 400;
	action_time = 0;
	action_type = 0;
	action_type = GetRand(4);

}

void EnemyGhost::Update()
{

	GhostMove();
	GhostAttack();

}

void EnemyGhost::Draw()const
{

	DrawCircle(ghost_x, ghost_y, 15, GetColor(255, 0, 255), TRUE);

}

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

void EnemyGhost::GhostAttack()
{



}