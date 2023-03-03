#pragma once
#include "Define.h"

class EfectExplosion
{
private:

	int explosion_image;
	int trance;
	int magni;
	Location location;

	bool delete_flg;
public:

	EfectExplosion();
	EfectExplosion(float,float);
	~EfectExplosion() {};
	void Draw() const;
	void Update();

	bool GetDeleteFlg() { return delete_flg; }
};