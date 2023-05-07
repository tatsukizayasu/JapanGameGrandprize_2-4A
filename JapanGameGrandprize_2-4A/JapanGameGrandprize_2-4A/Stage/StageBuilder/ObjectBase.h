#pragma once
#include "../../Define.h"
#include "../../ColliderBase.h"
#include "../../TextureContainer.h"

 //•Û‘¶ “Ç‚Ýž‚Ý‚ÉŽg‚¤ƒL[--------------------------------------
#define OBJECT_NAME_DEFAULT "object"
//--------------------------------------------------------------


class ObjectBase
{
private:
	const char* class_name = OBJECT_NAME_DEFAULT;
	std::string texture_name;
	int image;
	ColliderBase* collider;
	SphereCollider* pivot;
	Location vector;
	Location old_location;
	bool is_reverse;

	void ColliderCast(ColliderBase* p_collider);
public:
	ObjectBase();
	ObjectBase(Location pivot, ColliderBase* p_collider , std::string texture_name);
	~ObjectBase();

	void Draw()const;

	void DrawCollider()const;

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
	const char* GetObjectName() { return class_name; }
	const char* GetTextureName() { return texture_name.c_str(); }
	Location GetVector() { return vector; }

};