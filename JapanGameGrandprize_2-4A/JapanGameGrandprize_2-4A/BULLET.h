#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
class Bullet
{
protected:
	int damage;          //弾のダメージ
	int efect_count;	 //エフェクトの時間
	float scrool_x;      //弾のスクロールの値
	bool delete_flg;     //弾の削除フラグ
	bool efect_end;		 //エフェクトの終わりフラグ

	EfectExplosion* efect_explosion;
public:
	Bullet();
	Bullet(float,float);
	~Bullet() {};

	virtual void Draw() const = 0;
	virtual void Update() = 0;

	bool GetEfectFlg();
};