#include "SphereCollider.h"
#include "CameraWork.h"
#define _USE_MATH_DEFINES
#include <math.h>

//---------------------
// 描画
//---------------------
void SphereCollider::Draw()const
{

	DrawCircleAA(GetLocation().x - CameraWork::GetCamera().x, 
		GetLocation().y - CameraWork::GetCamera().y,
		GetRadius(),10, GetColor(128, 128, 128), TRUE);
}

bool SphereCollider::HitSphere(const SphereCollider* sphere_collider) const
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

bool SphereCollider::HitBox(const BoxCollider* box_collider) const
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
	sphere_y = location.y + (radius * sinf(rad));

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((sub_x[0] <= sphere_x) && (sphere_x <= sub_x[1]) && (sub_y[0] <= sphere_y) && (sphere_y <= sub_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitLine(const LineCollider* line_collider) const
{
	bool is_hit = false;
	Location vector1 =
		line_collider->GetLocation(LINE_END)
		- line_collider->GetLocation(LINE_START);
	Location vector2 =
		GetLocation() - line_collider->GetLocation(LINE_START);

	float len = powf(vector1.x * vector1.x + vector1.y * vector1.y, 0.5);

	Location unit_vector;
	unit_vector.x = vector1.x / len;
	unit_vector.y = vector1.y / len;

	float distance_near_pos = unit_vector.x * vector2.x
		+ unit_vector.y * vector2.y;

	Location near_pos;

	near_pos.x = unit_vector.x * distance_near_pos;
	near_pos.y = unit_vector.y * distance_near_pos;

	float distance_sphere_near_pos;

	distance_sphere_near_pos =
		powf(powf(near_pos.x - vector2.x, 2.0) + powf(near_pos.y - vector2.y, 2.0), 0.5);

	if (distance_sphere_near_pos > GetRadius())
	{
		return false;
	}

	bool is_start_acute =
		CheckIsAcute(line_collider->GetLocation(LINE_END)
		- line_collider->GetLocation(LINE_START), vector2);
	bool is_end_acute
		= CheckIsAcute(
			line_collider->GetLocation(LINE_END)
			- line_collider->GetLocation(LINE_START)
			, GetLocation() - line_collider->GetLocation(LINE_END));

	if (is_start_acute ^ is_end_acute)
	{
		is_hit = true;
	}

	float distance_tips_sphere
		= MakeScalar(GetLocation() - line_collider->GetLocation(LINE_START));
	if (distance_tips_sphere <= GetRadius())
	{
		is_hit = true;
	}
	distance_tips_sphere
		= MakeScalar(GetLocation() - line_collider->GetLocation(LINE_END));
	if (distance_tips_sphere <= GetRadius())
	{
		is_hit = true;
	}

	return is_hit;
}

//---------------------------------
// PolyLineとの当たり判定
//---------------------------------
bool SphereCollider::HitPolyLine(const class PolyLine* poly_line)const
{
	bool is_hit = false;
	const vector<LineCollider*>* lines = poly_line->GetLines();

	for (auto line : *lines)
	{
		if (HitLine(line))
		{
			is_hit = true;
			break;
		}
	}

	return is_hit;
}

//-------------------------------
// 当たり判定チェック
//------------------------------
bool SphereCollider::HitCheck(ColliderBase* collider)const
{
	bool is_hit = false;

	int class_type = collider->GetColliderType();
	switch (class_type)
	{
	case (int)COLLIDER::MAP_CHIP:
		is_hit = HitBox(static_cast<BoxCollider*>(collider));
		break;

	case (int)COLLIDER::SPHERE:
		is_hit = HitSphere(static_cast<SphereCollider*>(collider));
		break;

	case (int)COLLIDER::BOX:
		is_hit = HitBox(static_cast<BoxCollider*>(collider));
		break;

	case (int)COLLIDER::LINE:
		is_hit = HitLine(static_cast<LineCollider*>(collider));
		break;

	case (int)COLLIDER::POLY_LINE:
		collider = static_cast<PolyLine*>(collider);
		is_hit = HitPolyLine(static_cast<PolyLine*>(collider));
		break;

	default:
		break;
	}

	return is_hit;
}