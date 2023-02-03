#define _USE_MATH_DEFINES
#include<math.h>
#include "BoxCollider.h"
#include"SphereCollider.h"


bool SphereCollider::HitSphere(SphereCollider* sphere_collider)
{
	bool ret = false;//•Ô‚è’l
	float distance;	//’†SÀ•W‚Ì‹——£

	//’†SÀ•W‚Ì‹——£‚ÌŒvŽZ
	distance = sqrtf(powf(sphere_collider->GetLocation().x - location.x, 2) + powf(sphere_collider->GetLocation().y - location.y, 2));

	if (distance < radius + sphere_collider->GetRadius()) //“–‚½‚è”»’è
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitBox(class BoxCollider* box_collider)
{
	bool ret = false; //•Ô‚è’l
	float rad; //2“_‚ÌŠp“x
	float sphere_x; //‰~‚ÌÀ•W(x)
	float sphere_y; //‰~‚ÌÀ•W(y)

	//Šp“x‚ÌŒvŽZ
	rad = atan2f(box_collider->GetLocation().y - location.y, box_collider->GetLocation().x - location.x);

	//À•W‚ÌŒvŽZ
	sphere_x = location.x + (radius * cosf(rad));
	sphere_y = location.y - (radius * sinf(rad));

	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	//float px1 = location.x - (box_collider.GetErea().width / 2);
	//float py1 = location.y - (box_collider.GetErea().height / 2);
	float px1 = box_collider->GetLocation().x;
	float py1 = box_collider->GetLocation().y;
	float px2 = px1 + box_collider->GetArea().width;
	float py2 = py1 + box_collider->GetArea().height;


	if ((px1 < sphere_x) && (sphere_x < px2) && (py1 < sphere_y) && (sphere_y < py2)) //“–‚½‚è”»’è
	{
		ret = true;
	}

	return ret;
}
