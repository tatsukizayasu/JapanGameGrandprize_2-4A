#pragma once
#include "../../Define.h"
#include "../../ColliderBase.h"

class ObjectBase
{
private:
	ColliderBase* collider;
	int image;
	SphereCollider* pivot;
	Location vector;
	bool is_reverse;

	void ColliderCast(ColliderBase* p_collider);
public:
	ObjectBase();
	ObjectBase(Location pivot, ColliderBase* p_collider );
	~ObjectBase();

	void Draw()const;

	void UpdateColliderPos();

	bool HitSphere(SphereCollider* sphere)
	{
		return collider->HitSphere(sphere);
	}
	
	bool HitBox(BoxCollider* box)
	{
		return collider->HitBox(box);
	}
	
	bool HitLine(LineCollider* line)
	{
		return collider->HitLine(line);
	}

	ColliderBase* GetColllider()const { return collider; }
	SphereCollider* GetPivot()const { return pivot; }
};


