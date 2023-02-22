#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlime.h"

#define ATTACK_DISTANCE_Y 15
#define ATTACK_SPEED 5

#define SLIME_ATTACK_DAMAGE 10

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
	case ENEMY_STATE::IDOL:
		break;

	case ENEMY_STATE::MOVE:
		break;

	case ENEMY_STATE::ATTACK:
		Attack();
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
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

//-----------------------------------
//ƒAƒCƒhƒ‹ó‘Ô
//-----------------------------------
void EnemySlime::Idol()
{

}

//-----------------------------------
//ˆÚ“®
//-----------------------------------
void EnemySlime::Move(const Location player_location)
{

	if (location.x >= 1260)
	{
		location.x += -speed ;
	}
	if (location.x <= 20)
	{
		location.x += speed;
	}
	
}


//-----------------------------------
//UŒ‚
//-----------------------------------
AttackResource EnemySlime::Attack(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //–ß‚è’l

	if (HitBox(collider))
	{
		ENEMY_TYPE attack_type[1] = { *type };
		ret.damage = SLIME_ATTACK_DAMAGE;
		ret.type = attack_type;
		ret.type_count = 1;
		KnockBack();
	}

	return ret;
}

//-----------------------------------
//Ž€–S
//-----------------------------------
void EnemySlime::Death()
{
	location.x -= speed * direction;
	slime_angle -= 15 * direction;
	if (slime_angle >= 880 || slime_angle <= -880)
	{
		slime_angle = 180;
		
	}
}

void EnemySlime::HitStage()
{

}

void EnemySlime::AttackJudgement(const BoxCollider* boxcollider)
{
	if (!CheckHp())
	{
		if (boxcollider->HitBox(new EnemySlime(location.x + (60 * direction) - CameraWork::GetCamera().x, location.y - 20, 80, 80)))
		{
			color = GetColor(255, 0, 0);

			if (state == ENEMY_STATE::MOVE)
			{
				jump_distance.y = ATTACK_DISTANCE_Y;
				state = ENEMY_STATE::IDOL;
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
	if (location.y >= 490)
	{
		state = ENEMY_STATE::MOVE;
	}
}

void EnemySlime::KnockBack()
{
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;
	location.x += (ATTACK_SPEED * (direction * -1));
	if (CheckHp())
	{
		slime_angle -= 15 * direction;
	}
	if (location.y >= 490)
	{
		state = ENEMY_STATE::MOVE;
	}
}

