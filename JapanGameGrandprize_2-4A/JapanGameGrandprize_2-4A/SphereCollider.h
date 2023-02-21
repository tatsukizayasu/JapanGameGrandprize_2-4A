#pragma once
#include "define.h"
#include "ColliderBase.h"

class SphereCollider :public ColliderBase
{
protected:
	int radius;			//”¼Œa
public:

	//SphereCollider“–‚½‚è”»’è
	bool HitSphere(SphereCollider* sphere_collider);

	//BoxCollider“–‚½‚è”»’è
	bool HitBox(class BoxCollider* box_collider);

	bool HitLine(class LineCollider* line_collider);

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