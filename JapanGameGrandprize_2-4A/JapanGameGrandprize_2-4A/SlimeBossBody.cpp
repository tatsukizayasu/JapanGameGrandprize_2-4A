#include "SlimeBossBody.h"
#include "dxlib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include "Stage/Stage.h"

SlimeBossBody::SlimeBossBody(int x, int y, int height, int width)
{
	kind = ENEMY_KIND::SLIME;

	location.x = x;
	location.y = y;

	area.height = height;
	area.width = width;

	type = new ENEMY_TYPE;
	*type = ENEMY_TYPE::WATER;
}

SlimeBossBody::~SlimeBossBody()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;

}

void SlimeBossBody::Update(const Player* player, const Stage* stage)
{
}

void SlimeBossBody::Draw()const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, (area.height / 2), 0xff0000, true, true);
}

//-----------------------------------
//ÉAÉCÉhÉãèÛë‘
//-----------------------------------
void SlimeBossBody::Idol()
{
}

//-----------------------------------
//à⁄ìÆ
//-----------------------------------
void SlimeBossBody::Move(const Location player_location)
{
}

//-----------------------------------
//óéâ∫
//-----------------------------------
void SlimeBossBody::Fall()
{
}

//-----------------------------------
//çUåÇ
//-----------------------------------
void  SlimeBossBody::Attack(Location player_location)
{
}

//-----------------------------------
//çUåÇÇ™ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
//-----------------------------------
AttackResource SlimeBossBody::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //ñﬂÇËíl

	if (!attack)
	{
		attack = true;
		ENEMY_TYPE attack_type[1] = { *type };
		//ret.bless_se = SLIME_BOSS_ATTACK_DAMAGE;
		//ret.type = attack_type;
		ret.type_count = 1;
	}

	return ret;
}

//-----------------------------------
//éÄñS
//-----------------------------------
void SlimeBossBody::Death()
{
}

//-----------------------------------
// ÉvÉåÉCÉÑÅ[ÇÃíeÇ∆ÇÃìñÇΩÇËîªíË
//-----------------------------------
void SlimeBossBody::HitBullet(const BulletBase* bullet)
{
	PlayHitBulletSound(bullet->GetAttribute());

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
}

//-----------------------------------
//ç¿ïWÇÃéÊìæ
//-----------------------------------
Location SlimeBossBody::GetLocation() const
{
	return location;
}

void SlimeBossBody::SetLocation(Location location)
{
	this->location.x = location.x;
	this->location.y = location.y;
}

#ifdef _DEBUG
//-----------------------------------
// çXêV(DotByDot)
//-----------------------------------
void SlimeBossBody::Update(const ENEMY_STATE state)
{
	if ((old_state != state))
	{
		location = debug_location;
	}

	old_state = state;
}

//-----------------------------------
//ï`âÊ(DotByDot)
//-----------------------------------
void SlimeBossBody::DebugDraw()
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, 15, 0xff0000, true, true);
}
#endif //_DEBUG