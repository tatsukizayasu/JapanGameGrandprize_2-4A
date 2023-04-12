#pragma once
#include "DxLib.h"
#include "BULLET.h"
#include "Define.h"
#include "SphereCollider.h"

#define PIXEL_MAX 4

class NormalBullet : public BulletBase
{
private:

	int Tick;
	float speed_x, speed_y[PIXEL_MAX];
	float dot_location_x[PIXEL_MAX], dot_location_y[PIXEL_MAX];
	Bullet_Effect Explosion[4];	//0:ñ{íeÅ@1:îgìÆ(î≠éÀéû) 2:îgìÆÅ@3:ãOê’
	Bullet_Effect Melt[2];		//0:ñ{íeÅ@1:ãOê’
	Bullet_Effect Paralysis[2];	//0:ñ{íeÅ@1:ãOê’
	Bullet_Effect Poison[2];	//0:ñ{íeÅ@1:ãOê’
public:

	NormalBullet();
	NormalBullet(float, float,bool,ChemicalFormulaParameter*);
	~NormalBullet() {}

	void Draw() const override;
	void Update(const Stage*) override;

	bool NormalBulletEfect();
};