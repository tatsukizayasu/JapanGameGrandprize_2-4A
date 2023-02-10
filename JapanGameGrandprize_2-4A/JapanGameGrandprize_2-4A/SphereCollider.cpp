#include "SphereCollider.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include <math.h>

#define _USE_MATH_DEFINES

bool SphereCollider::HitSphere(SphereCollider* sphere_collider)
{
	bool ret = false;//返り値
	float distance;	//中心座標の距離

	//中心座標の距離の計算
	distance = sqrtf(powf(sphere_collider->GetLocation().x - location.x, 2) + powf(sphere_collider->GetLocation().y - location.y, 2));

	if (distance < radius + sphere_collider->GetRadius()) //当たり判定
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitBox(class BoxCollider* box_collider)
{
	bool ret = false; //返り値
	float rad; //2点の角度
	float sphere_x; //円の座標(x)
	float sphere_y; //円の座標(y)

	//相手の当たり判定の範囲
	float sub_x[2];
	float sub_y[2];

	//角度の計算
	rad = atan2f(box_collider->GetLocation().y - location.y, box_collider->GetLocation().x - location.x);

	//座標の計算
	sphere_x = location.x + (radius * cosf(rad));
	sphere_y = location.y - (radius * sinf(rad));

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;


	if ((sub_x[0] < sphere_x) && (sphere_x < sub_x[1]) && (sub_y[0] < sphere_y) && (sphere_y < sub_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitLine(class LineCollider* line_collider)
{
	bool ret = false; //返り値

	float vector_x[3]; //X座標のベクトル
	float vector_y[3]; //Y座標のベクトル

	float unit_vector;	//単位ベクトル
	float shortest_distance; //線分と円の最短の距離

	float inner_product[2]; //内積(0:x,1:y)
	float center_distance[2]; //円の中心との距離(0:線分の始点　1:線分の終点)

	//LineColliderの始点と終点とのベクトルの計算
	vector_x[0] = line_collider->GetLocation(1).x - line_collider->GetLocation(0).x;
	vector_y[0] = line_collider->GetLocation(1).y - line_collider->GetLocation(0).y;

	//LineColliderの始点とphereColliderの中心とのベクトルの計算
	vector_x[1] = location.x - line_collider->GetLocation(0).x;
	vector_y[1] = location.y - line_collider->GetLocation(0).y;

	//LineColliderの終点とSphereColliderの中心とのベクトルの計算
	vector_x[2] = location.x - line_collider->GetLocation(1).x;
	vector_y[2] = location.y - line_collider->GetLocation(1).y;

	//単位ベクトルの計算
	unit_vector = sqrt(pow(vector_x[0], 2) + pow(vector_y[0], 2));

	//最短距離の計算
	shortest_distance = (vector_x[1] * (vector_x[0] / unit_vector)) - (vector_y[1] * (vector_y[0] / unit_vector));

	if (fabsf(shortest_distance) <= radius)
	{
		//内積の計算
		for (int i = 0; i < 2; i++)
		{
			inner_product[i] = (vector_x[i + 1] * vector_x[0]) - (vector_y[i + 1] * vector_y[0]);
		}
		//円の中心との距離の計算
		for (int i = 0; i < 2; i++)
		{
			center_distance[i] = sqrt(pow(vector_x[i + 1], 2) + pow(vector_y[i + 1], 2));
		}

		if ((inner_product[0] * inner_product[1] <= 0.0f) || (center_distance[0] < radius) ||
			(center_distance[1] < radius))
		{
			ret = true;
		}
	}

	return ret;
}