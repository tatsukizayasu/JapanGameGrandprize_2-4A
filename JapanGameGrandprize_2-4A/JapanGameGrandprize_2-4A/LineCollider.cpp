#define _USE_MATH_DEFINES
#include<math.h>
#include "LineCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

bool LineCollider::HitSphere(class SphereCollider* sphere_collider)
{

}

bool LineCollider::HitBox(class BoxCollider* box_collider)
{

}

bool LineCollider::HitLine(LineCollider* line_collider)
{
	//自分のLineColliderの始点を起点にして出たベクトル
	float vec_p[3];

	//相手のLineColliderの始点を起点にして出たベクトル
	float vec_m[3];

	//自分のLineColliderのベクトル
	vec_p[0] = fabsf((location[0].x * location[1].x) - (location[0].y * location[1].y));

	//自分のLineColliderの始点と相手のLineColliderの始点のベクトル
	vec_p[1] = fabsf((line_collider->GetLocation(0).x * location[1].x) - (line_collider->GetLocation(0).x * location[0].y));

	//自分のLineColliderの始点と相手のLineColliderの終点のベクトル
	vec_p[2] = fabsf((line_collider->GetLocation(1).x * location[1].x) - (line_collider->GetLocation(1).x * location[0].y));


	//相手のLineColliderのベクトル
	vec_m[0] = fabsf((line_collider->GetLocation(0).x * line_collider->GetLocation(1).x) - (line_collider->GetLocation(0).y * line_collider->GetLocation(1).y));

	//相手のLineColliderの始点と相手のLineColliderの始点のベクトル
	vec_m[1] = fabsf((line_collider->GetLocation(0).x * location[1].x) - (line_collider->GetLocation(0).x * location[0].y));

	//相手のLineColliderの始点と相手のLineColliderの終点のベクトル
	vec_m[2] = fabsf((line_collider->GetLocation(1).x * location[1].x) - (line_collider->GetLocation(1).x * location[0].y));
}