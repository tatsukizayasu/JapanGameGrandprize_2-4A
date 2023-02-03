#include "BoxCollider.h"
#include"SphereCollider.h"
#define _USE_MATH_DEFINES
#include<math.h>


//SphereCollider‚Æ‚Ì“–‚½‚è”»’è
bool BoxCollider::HitSphere(class SphereCollider* sphere_collider)
{
	bool ret = false;//•Ô‚è’l
	float rad; //2“_‚ÌŠp“x
	float sphere_x; //‰~‚ÌÀ•W(x)
	float sphere_y; //‰~‚ÌÀ•W(y)

	//Šp“x‚ÌŒvŽZ
	rad = atan2f(sphere_collider->GetLocation().y - location.y, sphere_collider->GetLocation().x - location.x);

	//À•W‚ÌŒvŽZ
	sphere_x = sphere_collider->GetLocation().x + (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y + (sphere_collider->GetRadius() * sinf(rad));

	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float mx1 = location.x - (area.width / 2);
	float my1 = location.y - (area.height / 2);
	float mx2 = mx1 - area.width;
	float my2 = my1 - area.height;


	if ((mx1 > sphere_x) && (mx2 < sphere_x) && (my1 > sphere_y) && (my2 < sphere_y)) //“–‚½‚è”»’è
	{
		ret = true;
	}

	return ret;
}

//BoxCollider‚Æ‚Ì“–‚½‚è”»’è
bool BoxCollider::HitBox(BoxCollider* box_collider)
{
	bool ret = false; //•Ô‚è’l

	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	//float mx1 = location.x - (erea.width / 2);
	//float my1 = location.y - (erea.height / 2);
	float mx1 = location.x;
	float my1 = location.y;
	float mx2 = mx1 + area.width;
	float my2 = my1 + area.height;

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	//float px1 = box_collider.GetLocation().x - (box_collider.GetErea().width / 2);
	//float py1 = box_collider.GetLocation().x - (box_collider.GetErea().height / 2);
	float px1 = box_collider->GetLocation().x;
	float py1 = box_collider->GetLocation().y;
	float px2 = px1 + box_collider->GetArea().width;
	float py2 = py1 + box_collider->GetArea().height;

	if ((mx1 < px2) && (px1 < mx2) && (my1 < py2) && (py1 < my2)) //“–‚½‚è”»’è
	{
		ret = true;
	}
	return ret;
}

//’†SÀ•W‚ÌŽæ“¾
Location BoxCollider::GetLocation()const
{
	return location;
}

//”¼Œa‚ÌŽæ“¾
Area BoxCollider::GetArea()const
{
	return area;
}

//’†SÀ•W‚ÌÝ’è
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}