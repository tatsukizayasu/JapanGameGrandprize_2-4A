#define _USE_MATH_DEFINES
#include<math.h>
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "LineCollider.h"



//SphereColliderとの当たり判定
bool BoxCollider::HitSphere(class SphereCollider* sphere_collider)
{
	bool ret = false;//返り値
	float rad; //2点の角度
	float sphere_x; //円の座標(x)
	float sphere_y; //円の座標(y)

	//自分の当たり判定の範囲
	float my_x[2];
	float my_y[2];

	//角度の計算
	rad = atan2f(sphere_collider->GetLocation().y - location.y, sphere_collider->GetLocation().x - location.x);

	//座標の計算
	sphere_x = sphere_collider->GetLocation().x + (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y + (sphere_collider->GetRadius() * sinf(rad));

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] - area.width;
	my_y[1] = my_y[0] - area.height;


	if ((sphere_x < my_x[0]) && (my_x[1] < sphere_x) && (sphere_y < my_y[0]) && (my_y[1] < sphere_y)) //当たり判定
	{
		ret = true;
	}

	return ret;
}

//BoxColliderとの当たり判定
bool BoxCollider::HitBox(BoxCollider* box_collider)
{
	bool ret = false; //返り値

	//自分の当たり判定の範囲
	float my_x[2];
	float my_y[2];

	//相手の当たり判定の範囲
	float sub_x[2];
	float sub_y[2];

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().x - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((my_x[0] < sub_x[1]) && (sub_x[0] < my_x[1]) && (my_y[0] < sub_y[1]) && (sub_y[0] < my_y[1])) //当たり判定
	{
		ret = true;
	}
	return ret;
}

//LineColliderとの当たり判定
bool BoxCollider::HitLine(LineCollider* line_collider)
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
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = sub_x[0] + area.width;
	my_y[1] = sub_y[0] + area.height;

	//相手の当たり判定の範囲の計算
	if (line_collider->GetLocation(0).x <= line_collider->GetLocation(1).x)
	{
		sub_x[0] = line_collider->GetLocation(0).x;
		sub_x[1] = line_collider->GetLocation(1).x;

	}
	else
	{
		sub_x[0] = line_collider->GetLocation(1).x;
		sub_x[1] = line_collider->GetLocation(0).x;
	}

	if (line_collider->GetLocation(0).y <= line_collider->GetLocation(1).y)
	{
		sub_y[0] = line_collider->GetLocation(0).y;
		sub_y[1] = line_collider->GetLocation(1).y;
	}
	else
	{
		sub_y[0] = line_collider->GetLocation(1).y;
		sub_y[1] = line_collider->GetLocation(0).y;
	}


	if ((my_x[0] < sub_x[1]) && (my_x[1] < sub_x[1]) && (my_y[0] < sub_y[1]) && (sub_y[0] < my_y[1]))
	{
		//LineColliderの始点と終点とのベクトルの計算
		vector_x[0] = line_collider->GetLocation(1).x - line_collider->GetLocation(0).x;
		vector_y[0] = line_collider->GetLocation(1).y - line_collider->GetLocation(0).y;

		//自分のLineColliderの始点と左上の角とのベクトル
		vector_x[1] = location.x - line_collider->GetLocation(0).x;
		vector_y[1] = location.y - line_collider->GetLocation(0).y;

		//自分のLineColliderの始点と右下の角とのベクトル
		vector_x[2] = (location.x + area.width) - line_collider->GetLocation(0).x;
		vector_y[2] = (location.y + area.height) - line_collider->GetLocation(0).y;

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
}
//中心座標の取得
Location BoxCollider::GetLocation()const
{
	return location;
}

//半径の取得
Area BoxCollider::GetArea()const
{
	return area;
}

//中心座標の設定
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}