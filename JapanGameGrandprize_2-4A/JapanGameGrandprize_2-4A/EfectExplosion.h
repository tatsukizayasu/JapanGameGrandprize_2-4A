#pragma once
#include "Define.h"

class EffectExplosion
{
private:

	int explosion_image;
	int trance;
	int magni;
	Location location;

	bool delete_flg;
public:

	EffectExplosion();
	EffectExplosion(float,float);
	~EffectExplosion() {};
	void Draw() const;
	void Update();

	bool GetDeleteFlg() { return delete_flg; }
};