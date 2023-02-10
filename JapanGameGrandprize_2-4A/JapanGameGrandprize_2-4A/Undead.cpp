#include "Undead.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Undead::Undead()
{
	/*初期化*/
	kind = ENEMY_KIND::UNDEAD;
	type = ENEMY_TYPE::NORMAL;
	state = UNDEAD_STATE::IDOL;


}

//-----------------------------------
// デストラクタ
//-----------------------------------
Undead::~Undead()
{

}

//-----------------------------------
// 更新
//-----------------------------------
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

//-----------------------------------
// 攻撃
//-----------------------------------
void Undead::Attack()
{

}

//-----------------------------------
// 描画
//-----------------------------------
void Undead::Draw() const
{

}