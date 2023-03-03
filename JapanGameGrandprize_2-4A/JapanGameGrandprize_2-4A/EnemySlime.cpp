#include<dxlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemySlime.h"

#define SLIME_ATTACK_DISTANCE_Y 15
#define SLIME_ATTACK_SPEED 5

//移動速度
#define SLIME_SPEED 2
#define SLIME_ATTACK_DAMAGE 10

#define SLIME_MIN_DROP 0u
#define SLIME_MAX_DROP 3u

EnemySlime::EnemySlime()
{
	kind = ENEMY_KIND::SLIME;

	location.x = 1100;
	location.y = 450;


	area.height = 40;
	area.width = 40;

	hp = 100;
	speed = SLIME_SPEED;

	color = GetColor(0, 0, 255);

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;

	state = ENEMY_STATE::MOVE;
	direction = DIRECTION::LEFT;
	slime_image = LoadGraph("Images/Enemy/Slime_.png");
	slime_angle = 0;

	//ドロップアイテムの設定
	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;

	for (int i = 0; i < WATER_DROP; i++)
	{
		volume = SLIME_MIN_DROP + GetRand(SLIME_MAX_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

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
		break;
	case ENEMY_STATE::DEATH:
		break;
	default:
		break;
	}

	if (CheckHp() && state != ENEMY_STATE::DEATH)
	{
		state = ENEMY_STATE::DEATH;
		jump_distance.y = 15;
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

	DrawRotaGraph(location.x - CameraWork::GetCamera().x, location.y - CameraWork::GetCamera().y, 0.17, M_PI / 180 * slime_angle, slime_image, TRUE);
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void EnemySlime::Idol()
{

}

//-----------------------------------
//移動
//-----------------------------------
void EnemySlime::Move(const Location player_location)
{
	if (location.x >= 1260)
	{
		direction = DIRECTION::LEFT;
		speed  = -SLIME_SPEED;
	}
	if (location.x <= 20)
	{
		direction = DIRECTION::RIGHT;
		speed = SLIME_SPEED;
	}
	location.x += speed;

	float distance; //離れている距離

	//プレイヤーとの距離の計算
	distance = sqrtf(powf(player_location.x - location.x, 2) + powf(player_location.y - location.y, 2));

	if (distance < 120)
	{
		state = ENEMY_STATE::ATTACK;
		jump_distance.y = SLIME_ATTACK_DISTANCE_Y;
	}
}

//-----------------------------------
//攻撃
//-----------------------------------
void  EnemySlime::Attack(Location player_location)
{
	location.y -= (jump_distance.y / 3);
	jump_distance.y -= 1;

	switch (slime_attack)
	{
	case SLIME_ATTACK::BEFORE_ATTACK:

		if (direction == DIRECTION::RIGHT)speed = SLIME_ATTACK_SPEED;
		else speed = -SLIME_ATTACK_SPEED;
		break;

	case SLIME_ATTACK::AFTER_ATTACK:

		if (direction == DIRECTION::RIGHT)speed = -SLIME_ATTACK_SPEED;
		else speed = SLIME_ATTACK_SPEED;

		break;
	}
	location.x += speed;

	if (location.y >= 450)
	{
		slime_attack = SLIME_ATTACK::BEFORE_ATTACK;
		state = ENEMY_STATE::MOVE;
		if (direction == DIRECTION::RIGHT)speed = SLIME_SPEED;
		else speed = -SLIME_SPEED;
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource EnemySlime::HitCheck(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (state == ENEMY_STATE::ATTACK)
	{
		if (HitBox(collider))
		{
			slime_attack = SLIME_ATTACK::AFTER_ATTACK;
			ENEMY_TYPE attack_type[1] = { *type };
			ret.damage = SLIME_ATTACK_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
		}
	}

	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void EnemySlime::Death()
{
	if (slime_angle >= 880 || slime_angle <= -880)
	{
		slime_angle = 880;
	}
	else
	{
		if (location.y <= 450)
		{
			location.y -= (jump_distance.y / 3);
			jump_distance.y -= 1;
		}
		if (direction == DIRECTION::RIGHT)
		{
			speed = -SLIME_ATTACK_SPEED;
			slime_angle -= 15;
		}
		else
		{
			speed = SLIME_ATTACK_SPEED;
			slime_angle += 15;
		}
		location.x += speed;
	}
}

//-----------------------------------
// プレイヤーの弾との当たり判定
//-----------------------------------
bool EnemySlime::HitBullet(const BulletBase* bullet)
{
	bool ret = false; //戻り値
	if (HitSphere(bullet))
	{
		switch (bullet->GetAttribute())
		{
		case ATTRIBUTE::NORMAL:
			hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
			break;
		case ATTRIBUTE::EXPLOSION:
			hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
			break;
		case ATTRIBUTE::MELT:
			hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
			break;
		case ATTRIBUTE::POISON:
			//poison_damage = bullet->GetDamage();
			//poison_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
			break;
		case ATTRIBUTE::PARALYSIS:
			paralysis_time = bullet->GetDebuffTime() * 0;
			break;
		case ATTRIBUTE::HEAL:
			break;
		default:
			break;
		}
		ret = true;
	}
	return ret;
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location EnemySlime::GetLocation() const
{
	return location;
}