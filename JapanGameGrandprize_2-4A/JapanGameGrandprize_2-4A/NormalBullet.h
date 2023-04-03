#pragma once
#include "DxLib.h"
#include "BULLET.h"
#include "Define.h"
#include "SphereCollider.h"

#define PIXEL_MAX 4

class NormalBullet : public BulletBase
{
private:

	float speed_x, speed_y[PIXEL_MAX];
	float dot_location_x[PIXEL_MAX], dot_location_y[PIXEL_MAX];
	Bullet_Effect Explosion[4];
	Bullet_Effect Melt[2];
	Bullet_Effect Poison[2];
public:

	NormalBullet();
	NormalBullet(float, float,bool,ChemicalFormulaParameter*);
	~NormalBullet() {}

	void Draw() const override;
	void Update(const Stage*) override;

	//void Explosion(float, float) const;
	//void Melt(float x, float y);
	//void Paralysis(float x, float y);

	bool NormalBulletEfect();
};