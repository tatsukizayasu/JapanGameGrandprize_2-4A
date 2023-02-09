#pragma once
#include "EfectExplosion.h"
class BULLET
{
private:
	float bullet_x, bullet_y;
	bool delete_flg;

	EfectExplosion* EfectExplosion;
public:
	BULLET();
	BULLET(float,float);
	~BULLET() {};

	void Draw()const;
	void Update();

	bool GetDeleteFlg() { return delete_flg; }
};

