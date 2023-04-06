#include "BoxCollider.h"
#include "SphereCollider.h"
#include "LineCollider.h"
#include "CameraWork.h"
#include <math.h>

#define _USE_MATH_DEFINES

//-----------------------------------
// コンストラクタ
//-----------------------------------
 BoxCollider::BoxCollider()
{

}

//-----------------------------------
// コンストラクタ
//-----------------------------------
 BoxCollider::BoxCollider(Location location, Area area):ColliderBase(location)
 {
	 this->area = area;

#ifdef _STAGE_BUILDER

	 pivot = new SphereCollider(location);

	 spheres = new SphereCollider * [4];

	 spheres[0] = new SphereCollider(
		 {
			 location.x - area.width / 2,location.y - area.height / 2
		 }
	 );

	 spheres[1] = new SphereCollider(
		 {
			 location.x + area.width / 2,location.y - area.height / 2
		 }
	 );

	 spheres[2] = new SphereCollider(
		 {
			 location.x - area.width / 2,location.y + area.height / 2
		 }
	 );

	 spheres[3] = new SphereCollider(
		 {
			 location.x + area.width / 2,location.y + area.height / 2
		 }
	 );

#endif
 }

//-----------------------------------
// デストラクタ
//-----------------------------------
 BoxCollider::~BoxCollider()
 {
#ifdef _STAGE_BUILDER
	 delete[] spheres;
	 delete pivot;
#endif
 }

 //----------------------------------
 // 描画
 //----------------------------------
 void BoxCollider::Draw()const
 {
	 DrawBoxAA(location.x - area.width / 2 - CameraWork::GetCamera().x, 
		 location.y - area.height / 2 - CameraWork::GetCamera().y,
		 location.x + area.width / 2 - CameraWork::GetCamera().x,
		 location.y + area.height / 2 - CameraWork::GetCamera().y
		 , 0xff00ff, FALSE);

#ifdef _STAGE_BUILDER

	 for (int i = 0; i < 4; i++)
	 {
		 if (spheres[i] != nullptr)
		 {
			spheres[i]->Draw();
		 }
	 }
	 if (pivot != nullptr)
	 {
		 pivot->Draw();
	 }

#endif
 }

//-----------------------------------
// SphereColliderとの当たり判定
//-----------------------------------
bool BoxCollider::HitSphere(const class SphereCollider* sphere_collider) const
{

	bool ret = false;//返り値
	float rad; //2点の角度
	float sphere_x; //円の座標(x)
	float sphere_y; //円の座標(y)

	//自分の当たり判定の範囲
	float my_x[2];
	float my_y[2];

	//角度の計算
	rad = atan2f(sphere_collider->GetLocation().y - location.y,
			      sphere_collider->GetLocation().x - location.x);

	//座標の計算
	sphere_x = sphere_collider->GetLocation().x 
		        + (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y 
		        + (sphere_collider->GetRadius() * sinf(rad));

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	if ((my_x[0] <= sphere_x) && (sphere_x <= my_x[1]) 
		    && (my_y[0] <= sphere_y) && (sphere_y <= my_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// BoxColliderとの当たり判定
//-----------------------------------
bool BoxCollider::HitBox(const BoxCollider* box_collider) const
{

	bool ret = false; //返り値

	//当たり判定範囲の誤差修正
	Area margin_area = { box_collider->margin_area.height, box_collider->margin_area.width };

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
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((my_x[0] <= sub_x[1] + margin_area.width) && (sub_x[0] + margin_area.width <= my_x[1])
		    && (my_y[0] <= sub_y[1] + margin_area.height) && (sub_y[0] +  margin_area.height <= my_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// LineColliderとの当たり判定
//-----------------------------------
bool BoxCollider::HitLine(const class LineCollider* line_collider) const
{
	bool is_hit = false;
	bool box_ishit = false;
	float sign = 0;

	Location vertex[4] =
	{
		//四隅
		{GetLocation().x - GetArea().width / 2,
		GetLocation().y - GetArea().height / 2 },

		{GetLocation().x + GetArea().width / 2,
		GetLocation().y - GetArea().height / 2 },

		{GetLocation().x - GetArea().width / 2,
		GetLocation().y + GetArea().height / 2 },

		{GetLocation().x + GetArea().width / 2,
		GetLocation().y + GetArea().height / 2},

	};

	for (int i = 0; i < 4; i++)
	{
		if ((line_collider->GetMin() <= vertex[i]) && 
			vertex[i] <= line_collider->GetMax())
		{
			box_ishit = true;
		}
	}
	if (box_ishit == false)return false; //線分を囲う四角形にすら当たってない


	for (int i = 0; i < 4; i++)
	{
		float closs_product = 0;

		Location vector1 =
			line_collider->GetLocation(LINE_START) -
			line_collider->GetLocation(LINE_END);
		Location vector2 =
			vertex[i] - line_collider->GetLocation(LINE_END);

		closs_product = (vector1.x * vector2.y) - (vector1.y * vector2.x);
		if (closs_product == 0)return true;	//0なら線と頂点が重なっているので当たり

		if (i == 0)
		{
			sign = closs_product;
		}
		else
		{
			if ((sign * closs_product) < 0)
			{
				is_hit = true;
				break;
			}
		}
	}

	return is_hit;
}

//-----------------------------------
// 中心座標の取得
//-----------------------------------
Location BoxCollider::GetLocation()const
{

	return location;
}

//-----------------------------------
// 半径の取得
//-----------------------------------
Area BoxCollider::GetArea()const
{

	return area;
}

//-----------------------------------
// 中心座標の設定
//-----------------------------------
void BoxCollider::SetLocation(Location location)
{

#ifdef _STAGE_BUILDER

	Location distance = location - this->location;

	pivot->SetLocation(location);
	for (int i = 0; i < 4; i++)
	{
		spheres[i]->SetLocation(spheres[i]->GetLocation() + distance);
	}

#endif

	this->location = location;

}

#ifdef _STAGE_BUILDER

//---------------------------------------
// 座標の更新 四角形になるように合わせる
//---------------------------------------
void BoxCollider::UpdatePos()
{
	for (int i = 0; i < 4; i++)
	{
		if (spheres[i]->GetLocation() != old_pos[i])
		{
			 //3から添え字を引くと対角の添え字になる。
			area.height = fabsf(spheres[3 - i]->GetLocation().y -
				spheres[i]->GetLocation().y);

			area.width = fabsf(spheres[3 - i]->GetLocation().x -
				spheres[i]->GetLocation().x);

			pivot->SetLocation(
				{
					(spheres[3 - i]->GetLocation() +
					spheres[i]->GetLocation()) / Location{2,2}
				}
			);


			break;
		}
	}

	SetLocation(pivot->GetLocation());

	spheres[0]->SetLocation
	({ location.x - area.width / 2,location.y - area.height / 2 });

	spheres[1]->SetLocation
	({ location.x + area.width / 2,location.y - area.height / 2 });

	spheres[2]->SetLocation
	({ location.x - area.width / 2,location.y + area.height / 2 });

	spheres[3]->SetLocation
	({ location.x + area.width / 2,location.y + area.height / 2 });

	for (int i = 0; i < 4; i++)
	{
		old_pos[i] = spheres[i]->GetLocation();
	}
}

#endif