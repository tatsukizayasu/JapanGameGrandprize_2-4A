#pragma once
#include "define.h"
#include "ColliderBase.h"


class SphereCollider :public ColliderBase
{
protected:

	int radius;			//”¼Œa
public:

	SphereCollider():ColliderBase()
	{
		collider_type = (int)COLLIDER::SPHERE;;
		radius = 5;
	}

	SphereCollider(Location location) :ColliderBase(location)
	{
		collider_type = (int)COLLIDER::SPHERE;
		radius = 5;
	}
	
	SphereCollider(Location location,float radius) :ColliderBase(location)
	{
		collider_type = (int)COLLIDER::SPHERE;
		this->radius = radius;
	}

	//•`‰æ
	virtual void Draw()const;

	//SphereCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitSphere(const class SphereCollider* sphere_collider) const override;

	//BoxCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitBox(const class BoxCollider* box_collider) const override;

	//LineCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitLine(const class LineCollider* line_collider) const override;

	//PolyLine‚Æ‚Ì“–‚½‚è”»’è
	virtual bool HitPolyLine(const class PolyLine* poly_line)const;

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