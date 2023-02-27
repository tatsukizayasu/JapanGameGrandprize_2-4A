#pragma once
#include "define.h"
#include "ColliderBase.h"

class SphereCollider :public ColliderBase
{
protected:

	int radius;			//”¼Œa
public:

	//SphereCollider“–‚½‚è”»’è
	bool HitSphere(const SphereCollider* sphere_collider) const;

	//BoxCollider“–‚½‚è”»’è
	bool HitBox(const class BoxCollider* box_collider) const;

	bool HitLine(const class LineCollider* line_collider) const;

	//’†SÀ•W‚ÌŽæ“¾
	Location GetLocation() const
	{
		return location;
	}

	//”¼Œa‚ÌŽæ“¾
	int GetRadius() const
	{
		return radius;
	}

	//’†SÀ•W‚ÌÝ’è
	void SetLocation(Location location)
	{
		this->location = location;
	}
};