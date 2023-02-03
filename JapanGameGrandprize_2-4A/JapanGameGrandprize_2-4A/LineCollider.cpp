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

	bool ret = false; //返り値

	/*自分のLineColliderの始点を起点にして出たベクトル*/
	float vec_x[3]; //X座標のベクトル
	float vec_y[3]; //Y座標のベクトル

	float outer_product[2]; //外積

	//自分のLineColliderの始点と終点とのベクトルの計算
	vec_x[0] = location[1].x - location[0].x;
	vec_y[0] = location[1].y - location[0].y;

	//自分のLineColliderの始点と相手のLineColliderの始点とのベクトルの計算
	vec_x[1] = line_collider->GetLocation(0).x - location[0].x;
	vec_y[1] = line_collider->GetLocation(0).y - location[0].y;

	//自分のLineColliderの始点と相手のLineColliderの終点とのベクトルの計算
	vec_x[2] = line_collider->GetLocation(1).x - location[0].x;
	vec_y[2] = line_collider->GetLocation(1).y - location[0].y;

	//外積の計算
	for (int i = 0; i < 2; i++)
	{
		outer_product[i] = (vec_x[0] * vec_y[i + 1]) - (vec_x[i + 1] * vec_y[0]);
	}

	//当たり判定の判断
	if (outer_product[0] * outer_product[1] <= 0.0f)
	{
		ret = true;
	}

	return ret;
}