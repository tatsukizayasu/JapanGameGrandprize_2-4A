#pragma once
#include "../../Define.h"
#include "../../ColliderBase.h"

class ObjectBase
{
private:
	class ColliderBase* collider;
	int image;
	SphereCollider* pivot;
	Location vector;
	bool is_reverse;

public:
	ObjectBase();
	ObjectBase(Location pivot);
	~ObjectBase();

	void Draw()const;

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


