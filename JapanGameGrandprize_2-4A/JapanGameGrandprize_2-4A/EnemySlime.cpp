#include<dxlib.h>
#include"EnemySlime.h"

EnemySlime::EnemySlime()
{
	hp = 5;
	speed = 1;
	slime_x = 1300;
	slime_y = 680;
}

void EnemySlime::Update()
{
	slime_x -= speed;
	if (slime_x <= -100) delete this;

	
}

void EnemySlime::Draw()const
{
	DrawCircle(slime_x, slime_y,10, 0xffffff, 1, 1);
}