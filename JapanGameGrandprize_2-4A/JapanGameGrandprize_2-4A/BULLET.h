#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
#include "define.h"
class BulletBase
{
protected:
	float damage;          //弾のダメージ
	float debuff_time;	 //弾の効果時間
	int efect_count;	 //エフェクトの時間
	float scrool_x;      //弾のスクロールの値
	bool delete_flg;     //弾の削除フラグ
	bool efect_end;		 //エフェクトの終わりフラグ


	ATTRIBUTE attribute;
	EfectExplosion* efect_explosion;
public:
	BulletBase();
	BulletBase(float,float);
	~BulletBase() {};

	virtual void Draw() const = 0;
	virtual void Update() = 0;

	bool GetEfectFlg();
	float GetDebuffTime();
	float GetDamage();
	ATTRIBUTE GetAttribute();

};