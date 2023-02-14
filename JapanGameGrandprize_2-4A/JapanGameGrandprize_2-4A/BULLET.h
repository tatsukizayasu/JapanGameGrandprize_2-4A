#pragma once
#include "EfectExplosion.h"
class Bullet
{
private:
	float bullet_x, bullet_y;
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