#pragma once
#include"EnemyBase.h"
class EnemyGhost: public EnemyBase
{
private:
	struct Ghost
	{
		int ghost_x;
		int ghost_y;
		int ghost_hp;
		bool ghost_lost;
	};
public:
	EnemyGhost();
};

