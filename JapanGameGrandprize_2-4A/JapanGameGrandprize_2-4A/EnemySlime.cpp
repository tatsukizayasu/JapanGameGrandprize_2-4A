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
	location.y = 450;


	area.height = 40;
	area.width = 40;

	hp = 5;
	speed = 2;

	color = GetColor(0, 0, 255);
	direction = left;

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;

	state = SLIME_STATE::MOVE;

	slime_image = LoadGraph("Images/Enemy/Slime_.png");
	slime_angle = 0;
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
	switch (state)
	{
	case SLIME_STATE::IDOL:
		static int idol_time;
		if (idol_time++ >= 50)
		{
			idol_time = 0;
			state = SLIME_STATE::ATTACK;
		}
		break;

	case SLIME_STATE::MOVE:

		
		if (!CheckHp())
		{
			location.x += speed * direction;
			if (location.x >= 1260)direction = left;
			if (location.x <= 20)direction = right;
		}
		else
		{
			location.x -= speed * direction;
			slime_angle -= 15 * direction;
			if (slime_angle >= 880 || slime_angle <= -880)
			{
				slime_angle = 180;
				state = SLIME_STATE::DEATH;
			}
		}
		break;

	case SLIME_STATE::ATTACK:
		Attack();
		break;

	case SLIME_STATE::KNOCKBACK:
		KnockBack();
		break;

	case SLIME_STATE::DEATH:
		break;
	default:
		break;
	}
}

void EnemySlime::Draw()const
{
	/*DrawCircle(location.x - CameraWork::GetCamera().x , location.y, 20, color, 1, 1);
	DrawCircle(location.x - CameraWork::GetCamera().x, location.y + 8, 7, 0x000000, 1, 1);
	DrawCircle(location.x - 7 - CameraWork::GetCamera().x, location.y - 6, 4, 0xffffff, 1, 1);
	DrawCircle(location.x + 7 - CameraWork::GetCamera().x, location.y - 6, 4, 0xffffff, 1, 1);
	DrawCircle(location.x - 7 + (1 * direction) - CameraWork::GetCamera().x, location.y - 6, 2, 0x000000, 1, 1);
	DrawCircle(location.x + 7 + (1 * direction) - CameraWork::GetCamera().x, location.y - 6, 2, 0x000000, 1, 1);
	DrawBox(location.x - (area.width / 2)-CameraWork::GetCamera().x, location.y - (area.height / 2), location.x - (area.width / 2) + area.width- CameraWork::GetCamera().x, location.y - (area.height / 2) + area.height, 0xffffff, 0);*/

	DrawRotaGraph(location.x - CameraWork::GetCamera().x, location.y, 0.17, M_PI / 180 * slime_angle, slime_image, TRUE);
}

void EnemySlime::HitPlayer(BoxCollider* boxcollider)
{
	if (!CheckHp())
	{
		if (boxcollider->HitBox(new EnemySlime(location.x - CameraWork::GetCamera().x, location.y, area.height, area.width)) && hp > 0)
		{
			hp--;

			if (CheckHp())jump_distance.y = 20, state = SLIME_STATE::KNOCKBACK;
			else if (state == SLIME_STATE::ATTACK)jump_distance.y = 0,state = SLIME_STATE::KNOCKBACK;
		}
	}
}

void EnemySlime::HitStage()
{

}

void EnemySlime::AttackJudgement(BoxCollider* boxcollider)
{
	if (!CheckHp())
	{
		if (boxcollider->HitBox(new EnemySlime(location.x + (60 * direction) - CameraWork::GetCamera().x, location.y - 20, 80, 80)))
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
}

void EnemySlime::Attack()
{
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;
	location.x += (ATTACK_SPEED * (direction));
	if (location.y >= 490)state = SLIME_STATE::MOVE;
}

void EnemySlime::KnockBack()
{
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;
	location.x += (ATTACK_SPEED * (direction * -1));
	if (CheckHp())slime_angle -= 15 * direction;
	if (location.y >= 490)state = SLIME_STATE::MOVE;
}

