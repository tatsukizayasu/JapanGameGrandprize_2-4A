#include "ColliderBase.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "LineCollider.h"

//-------------------------------
// 当たり判定チェック
//------------------------------
bool ColliderBase::HitCheck(ColliderBase* collider)const
{
	bool is_hit = false;

	collider = dynamic_cast<BoxCollider*>(collider);
	if (collider)
	{
		return HitBox(dynamic_cast<BoxCollider*>(collider));
	}

	collider = dynamic_cast<SphereCollider*>(collider);
	if (collider)
	{
		return HitSphere(dynamic_cast<SphereCollider*>(collider));
	}

	collider = dynamic_cast<LineCollider*>(collider);
	if (collider)
	{
		return HitLine(dynamic_cast<LineCollider*>(collider));
	}

	return is_hit;
}