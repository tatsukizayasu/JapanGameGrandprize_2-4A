#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlime.h"

#define ATTACK_DISTANCE_Y 15
#define ATTACK_SPEED 5


EnemySlime::EnemySlime()
{
	kind = ENEMY_KIND::SLIME;

	location.x = 1100;
	location.y = 494;
	area.height = 40;
	area.width = 40;

	hp = 5;
	speed = 2;

	color = GetColor(0, 0, 255);
	direction = left;

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;

	state = SLIME_STATE::MOVE;

	slime_image = LoadGraph("Images/Enemy/Slime.png");
}

EnemySlime::EnemySlime(float x, float y, float height, float width)
{
	location.x = x;
	location.y = y;
	area.height = height;
	area.width = width;
}

void EnemySlime::Update()
{
	if (CheckHp())state = SLIME_STATE::DEATH;

	switch (state)
	{
	case SLIME_STATE::IDOL:
		static int idol_time;
		if (idol_time++ >= 20)
		{
			idol_time = 0;
			state = SLIME_STATE::ATTACK;
		}

		break;

	case SLIME_STATE::MOVE:

		location.x += speed * direction;
		if (location.x >= 1260)direction = left;
		if (location.x <= 20)direction = right;
		break;

	case SLIME_STATE::ATTACK:
		Attack();
		break;

	case SLIME_STATE::BOUNCE:
		Attack();
		break;

	case SLIME_STATE::DEATH:
		//DropItem(*type, 0, 2).

		break;
	default:
		break;
	}
}

void EnemySlime::Draw()const
{
	DrawCircle(location.x, location.y, 20, color, 1, 1);
	DrawCircle(location.x, location.y + 8, 7, 0x000000, 1, 1);
	DrawCircle(location.x - 7, location.y - 6, 4, 0xffffff, 1, 1);
	DrawCircle(location.x + 7, location.y - 6, 4, 0xffffff, 1, 1);
	DrawCircle(location.x - 7 + (1 * direction), location.y - 6, 2, 0x000000, 1, 1);
	DrawCircle(location.x + 7 + (1 * direction), location.y - 6, 2, 0x000000, 1, 1);

	//DrawBox(location.x - (area.width / 2), location.y - (area.height / 2), location.x - (area.width / 2) + area.width, location.y - (area.height / 2) + area.height, 0xffffff, 0);
}

void EnemySlime::HitPlayer(BoxCollider* boxcollider)
{
	if (HitBox(boxcollider))
	{
		if (state == SLIME_STATE::ATTACK)
		{
			jump_distance.y = 0;
			state = SLIME_STATE::BOUNCE;
		}
	}
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
			jump_distance.y = ATTACK_DISTANCE_Y;
			state = SLIME_STATE::IDOL;
		}
	}
	else color = GetColor(0, 0, 255);
}

void EnemySlime::Attack()
{
	int bounce_direction = 1;
	if (state == SLIME_STATE::BOUNCE)bounce_direction = -1;
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;
	location.x += (ATTACK_SPEED * (direction * bounce_direction));
	if (location.y >= 490)
	{
		jump_distance.y = ATTACK_DISTANCE_Y;
		state = SLIME_STATE::MOVE;
	}
}

