#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
class Bullet : SphereCollider
{
private:
	Location location;
	bool delete_flg;

	EfectExplosion* efect_explosion;
public:
	Bullet();
	Bullet(float,float);
	~Bullet() {};

	void Draw()const;
	void Update();

	bool GetDeleteFlg() { return delete_flg; }
};