#include<dxlib.h>
#include"EnemySlime.h"

EnemySlime::EnemySlime()
{
	color = GetColor(0, 0, 255);
	hp = 5;
	speed = 2;
	location.x = 1100;
	location.y = 400;
	area.height = 40;
	area.width = 40;
	direction = left;
	a = 0;
}

EnemySlime::EnemySlime(float x, float y, float height, float width)
{
	color = GetColor(0, 0, 255);
	hp = 5;
	speed = 2;
	location.x = x;
	location.y = y;
	area.height = height;
	area.width = width;

	direction = left;
}

void EnemySlime::Update()
{
	
	location.x += speed * direction;
	if (location.x >= 1260)direction = left;
	if (location.x <= 20)direction = right;
}


void EnemySlime::Draw()const
{
	DrawCircle(location.x, location.y, 20, color, 1, 1);
	DrawFormatString(0, 20, 0xffffff, "%d", a);
	DrawBox(location.x - (area.width / 2), location.y - (area.height / 2), location.x - (area.width / 2) + area.width, location.y - (area.height / 2) + area.height, 0xffffff, 0);
}

void EnemySlime::Hit()
{
	a++;
}

void EnemySlime::HitStage()
{
	location.x = old_location_x;
	location.x = old_location_x;
}

void EnemySlime::Attack(BoxCollider* boxcollider)
{

	if (boxcollider->HitBox(new EnemySlime(location.x + (60 * direction), location.y - 20, 80, 80)))color = GetColor(255, 0, 0);
	//if (boxcollider->HitBox(new EnemySlime(a, b, 40, 40)))color = GetColor(255, 0, 0);
	else color = GetColor(0, 0, 255);
}