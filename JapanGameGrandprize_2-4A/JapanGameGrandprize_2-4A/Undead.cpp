#include "Undead.h"


Undead::Undead()
{
	/*èâä˙âª*/
	kind = ENEMY_KIND::UNDEAD;
	type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;


}

Undead::~Undead()
{

}

void Undead::Update()
{
	switch (state)
	{
	case UNDEAD_STATE::IDOL:
		break;
	case UNDEAD_STATE::MOVE:
		location.x += speed;
		break;
	case UNDEAD_STATE::ATTACK:
		break;
	case UNDEAD_STATE::DEATH:
		break;
	default:
		break;
	}
}


void Undead::Attack()
{

}

void Undead::Draw() const
{

}