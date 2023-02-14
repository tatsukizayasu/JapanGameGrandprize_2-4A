#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlime.h"

#define JUMP_RANGE_X 60
#define JUMP_RANGE_Y 30


EnemySlime::EnemySlime()
{
	location.x = 1100;
	location.y = 400;
	area.height = 40;
	area.width = 40;

	hp = 5;
	speed = 2;

	color = GetColor(0, 0, 255);
	direction = left;
	a = 0;

	state = SLIME_STATE::MOVE;
	jump_angle = 0;
}

EnemySlime::EnemySlime(float x, float y, float height, float width)
{
	location.x = x;
	location.y = y;
	area.height = height;
	area.width = width;

	hp = 5;
	speed = 2;

	color = GetColor(0, 0, 255);
	direction = left;

	state = SLIME_STATE::MOVE;
}

void EnemySlime::Update()
{
	switch (state)
	{
	case SLIME_STATE::IDOL:
		break;

	case SLIME_STATE::MOVE:

		location.x += speed * direction;
		if (location.x >= 1260)direction = left;
		if (location.x <= 20)direction = right;
		break;

	case SLIME_STATE::ATTACK:
		Attack();
		if (location.x >= 1260)direction = left;
		if (location.x <= 20)direction = right;
		break;
	case SLIME_STATE::DEATH:
		break;
	default:
		break;
	}




	
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
}

void EnemySlime::AttackJudgement(BoxCollider* boxcollider)
{

	if (boxcollider->HitBox(new EnemySlime(location.x + (60 * direction), location.y - 20, 80, 80)))
	{
		color = GetColor(255, 0, 0);
		if (state == SLIME_STATE::MOVE)
		{
			state = SLIME_STATE::ATTACK;
			if (direction == left)jump_angle = 0;
			else jump_angle = -180;
			attack_start.x = location.x + ((JUMP_RANGE_X / 2) * direction);
			attack_start.y = location.y;
		}
	}
	else color = GetColor(0, 0, 255);
}

void EnemySlime::Attack()
{
	location.y = (sin(jump_angle * M_PI / 180) * JUMP_RANGE_Y) + attack_start.y;
	location.x = (cos(jump_angle * M_PI / 180) * JUMP_RANGE_X) + attack_start.x;
	jump_angle += (5 * direction);

	if (jump_angle > 180)state = SLIME_STATE::MOVE;

}

