#define _USE_MATH_DEFINES
#include<math.h>
#include "LineCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

bool LineCollider::HitSphere(class SphereCollider* sphere_collider)
{

	bool ret = false; //返り値

	float vector_x[3]; //X座標のベクトル
	float vector_y[3]; //Y座標のベクトル

	float unit_vector;	//単位ベクトル
	float shortest_distance; //線分と円の最短の距離

	float inner_product[2]; //内積
	float center_distance[2]; //円の中心との距離(0:線分の始点　1:線分の終点)

	//自分のLineColliderの始点と終点とのベクトルの計算
	vector_x[0] = location[1].x - location[0].x;
	vector_y[0] = location[1].y - location[0].y;

	//自分のLineColliderの始点とphereColliderの中心とのベクトルの計算
	vector_x[1] = sphere_collider->GetLocation().x - location[0].x;
	vector_y[1] = sphere_collider->GetLocation().y - location[0].y;

	//自分のLineColliderの終点とSphereColliderの中心とのベクトルの計算
	vector_x[2] = sphere_collider->GetLocation().x - location[1].x;
	vector_y[2] = sphere_collider->GetLocation().y - location[1].y;

	//単位ベクトルの計算
	unit_vector = sqrt(pow(vector_x[0], 2) + pow(vector_y[0], 2));

	//最短距離の計算
	shortest_distance = (vector_x[1] * (vector_x[0] / unit_vector)) - (vector_y[1] * (vector_y[0] / unit_vector));

	if (fabsf(shortest_distance) <= sphere_collider->GetRadius())
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

		if ((inner_product[0] * inner_product[1] <= 0.0f) || (center_distance[0] < sphere_collider->GetRadius()) || 
			(center_distance[1] < sphere_collider->GetRadius()))
		{
			ret = true;
		}
	}

	return ret;
}

bool LineCollider::HitBox(class BoxCollider* box_collider)
{
	bool ret = false; //返り値

	float vector_x[3]; //X座標のベクトル
	float vector_y[3]; //Y座標のベクトル

	float outer_product[4]; //外積

	//自分の当たり判定の範囲
	float my_x[2];
	float my_y[2];

	//相手の当たり判定の範囲
	float sub_x[2];
	float sub_y[2];
	
	bool sign = false; //最初の外積の符号(true:正の数、false:負の数)

	//自分の当たり判定の範囲の計算
	if (location[0].x <= location[1].x)
	{
		my_x[0] = location[0].x;
		my_x[1] = location[1].x;

	}
	else
	{
		my_x[0] = location[1].x;
		my_x[1] = location[0].x;
	}

	if (location[0].y <= location[1].y)
	{
		my_y[0] = location[0].y;
		my_y[1] = location[1].y;
	}
	else
	{
		my_y[0] = location[1].y;
		my_y[1] = location[0].y;
	}

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;


	if ((my_x[0] < sub_x[1]) && (my_x[1] < sub_x[1]) && (my_y[0] < sub_y[1]) && (sub_y[0] < my_y[1]))
	{
		//自分のLineColliderの始点と終点とのベクトルの計算
		vector_x[0] = location[1].x - location[0].x;
		vector_y[0] = location[1].y - location[0].y;

		//自分のLineColliderの始点と左上の角とのベクトル
		vector_x[1] = box_collider->GetLocation().x - location[0].x;
		vector_y[1] = box_collider->GetLocation().y - location[0].y;

		//自分のLineColliderの始点と右下の角とのベクトル
		vector_x[2] = (box_collider->GetLocation().x + box_collider->GetArea().width) - location[0].x;
		vector_y[2] = (box_collider->GetLocation().y + box_collider->GetArea().height) - location[0].y;

		//各頂点と外積の計算
		for (int i = 0, n = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				outer_product[n++] = (vector_x[0] * vector_y[i]) - (vector_y[0] * vector_x[j]);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (outer_product[i] == 0) //外積の値が0なら当たっている
			{
				ret = true;
				break;
			}

			if (i == 0)
			{
				//右上の角との外積の符号の取得
				sign = signbit(outer_product[0]);
			}
			else
			{
			
				if (sign != signbit(outer_product[i]))	//左上の角との外積の符号が違ったら当たっている
				{
					ret = true;
					break;
				}
			}
		}
	}
	
	return ret;
}

bool LineCollider::HitLine(LineCollider* line_collider)
{

	bool ret = false; //返り値

	/*自分のLineColliderの始点を起点にして出たベクトル*/
	float vector_x[3]; //X座標のベクトル
	float vector_y[3]; //Y座標のベクトル

	float outer_product[2]; //外積

	//自分のLineColliderの始点と終点とのベクトルの計算
	vector_x[0] = location[1].x - location[0].x;
	vector_y[0] = location[1].y - location[0].y;

	//自分のLineColliderの始点と相手のLineColliderの始点とのベクトルの計算
	vector_x[1] = line_collider->GetLocation(0).x - location[0].x;
	vector_y[1] = line_collider->GetLocation(0).y - location[0].y;

	//自分のLineColliderの始点と相手のLineColliderの終点とのベクトルの計算
	vector_x[2] = line_collider->GetLocation(1).x - location[0].x;
	vector_y[2] = line_collider->GetLocation(1).y - location[0].y;

	//外積の計算
	for (int i = 0; i < 2; i++)
	{
		outer_product[i] = (vector_x[0] * vector_y[i + 1]) - (vector_x[i + 1] * vector_y[0]);
	}

	//当たり判定の判断
	if (outer_product[0] * outer_product[1] <= 0.0f)
	{
		ret = true;
	}

	return ret;
}