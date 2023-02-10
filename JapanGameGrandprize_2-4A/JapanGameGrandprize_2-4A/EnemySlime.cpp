#include<dxlib.h>
#include"EnemySlime.h"

EnemySlime::EnemySlime()
{
	hp = 5;
	speed = 1;
	location.x = 1300;
	location.y = 400;
	area.height = 40;
	area.width = 40;
	a = 0;
}

void EnemySlime::Update()
{
	location.x -= speed;
}


void EnemySlime::Draw()const
{
	DrawCircle(location.x, location.y, 20, 0xffffff, 1, 1);
	DrawFormatString(0, 20, 0xffffff, "%d", a);
}

void EnemySlime::Hit()
{
	a++;
}