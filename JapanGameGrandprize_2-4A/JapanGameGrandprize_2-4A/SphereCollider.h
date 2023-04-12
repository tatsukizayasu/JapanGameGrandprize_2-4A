#pragma once
#include "define.h"
#include "ColliderBase.h"

#define SPHERE_COLLIDER_NAME "SphereCollider"

class SphereCollider :public ColliderBase
{
protected:

	int radius;			//”¼Œa
public:

	SphereCollider():ColliderBase()
	{
		class_name = SPHERE_COLLIDER_NAME;
		radius = 5;
	}

	SphereCollider(Location location) :ColliderBase(location)
	{
		class_name = SPHERE_COLLIDER_NAME;
		radius = 5;
	}

	//•`‰æ
	virtual void Draw()const;

	//SphereCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitSphere(const class SphereCollider* sphere_collider) const override;

	//BoxCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitBox(const class BoxCollider* box_collider) const override;

	//LineCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitLine(const class LineCollider* line_collider) const override;

	ColliderBase* Copy()const override { return new SphereCollider(*this); }

	bool HitCheck(ColliderBase* collider)const override;

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