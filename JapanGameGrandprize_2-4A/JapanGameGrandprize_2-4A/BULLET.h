#pragma once
#include "EfectExplosion.h"
#include "EfectBeam.h"

enum class BULLET_TYPE
{
	NORMAL = 0,  //ノーマル弾
	EXPLOSION,   //爆発
	MELT,        //溶ける（酸）
	WARTER,      //水
	POISON,      //毒（継続ダメ）
	PARALYSIS,   //麻痺（移動速度低下）
	FROZEN,      //氷（一定時間硬直）
	SPECIAL      //必殺技（ウランを使用してビーム）
};



class BULLET
{
private:
	float bullet_x, bullet_y;
	bool delete_flg;
	BULLET_TYPE type;

	EfectExplosion* efect_explosion;
	EfectBeam* efect_beam;

public:
	BULLET();
	BULLET(float,float,BULLET_TYPE);
	~BULLET() {};

	void Draw()const;
	void Update();

	bool GetDeleteFlg() { return delete_flg; }
};