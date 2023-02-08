#include<dxlib.h>
#include"EnemySlime.h"

EnemySlime::EnemySlime()
{
	hp = 5;
	speed = 1;
	location.x = 1300;
	location.y = 680;
	radius = 20;
	a = 0;
}

void EnemySlime::Update()
{
	location.x -= speed;
	//if (slime_x <= -100);
}


void EnemySlime::Draw()const
{
	DrawCircle(location.x + 20, location.y + 20,radius, 0xffffff, 1, 1);
}

void EnemySlime::Hit()
{
	a++;
}