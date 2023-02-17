#pragma once
#include "DxLib.h"
#include "BULLET.h"
#include "SphereCollider.h"

#define PIXEL_MAX 4

class NormalBullet : public Bullet, public SphereCollider
{
private:
	float speed_x, speed_y[PIXEL_MAX];
	float dot_location_x[PIXEL_MAX], dot_location_y[PIXEL_MAX];
public:
	NormalBullet();
	NormalBullet(float, float);
	~NormalBullet() {}

	void Draw() const override;
	void Update() override;

	bool NormalBulletEfect();
};