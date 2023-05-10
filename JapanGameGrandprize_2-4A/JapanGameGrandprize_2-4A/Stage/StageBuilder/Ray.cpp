#include "Ray.h"

//------------------------------
// コンストラクタ
//------------------------------
Ray::Ray()
{
	
}

//------------------------------
// コンストラクタ
//------------------------------
Ray::Ray(const Location* location, float shift_x, float shift_y) :base_location(location)
{
	LineCollider::SetLocation(Location{ 0,0 }, LINE_START);
	LineCollider::SetLocation(Location{ 0,100 }, LINE_END);
	Location base_location = *(this->base_location);

	LineCollider::ColliderBase::SetLocation
	(
		base_location - LineCollider::GetVector(LINE_START)
	);

	hit_collider_type = COLLIDER::NONE;
	shift = Location{ shift_x,shift_y };
}

//------------------------------
// デストラクタ
//------------------------------
Ray::~Ray()
{

}

//--------------------------
// 更新
//--------------------------
void Ray::Update()
{
	UpdateLocation();
	//まだ当たっているか確認して当たってなければ消す
	for (int i = 0; i < hit_colliders.size(); i++)
	{

		if (HitCheck(hit_colliders[i]) == false)
		{
			hit_colliders.erase(hit_colliders.begin() + i);
		}

	}
	location;
}

//----------------------------------------
// 描画
//----------------------------------------
void Ray::Draw()const
{
#ifdef _DEBUG
	LineCollider::Draw();

	int i = 0;
	for (ColliderBase* hit_collider : hit_colliders )
	{
		DrawFormatString(500, 100 + i*20, 0xFFFF00, "%d", hit_collider->GetColliderType());
		i++;
	}
#endif 
}

//----------------------------------
// 場所の更新
//----------------------------------
void Ray::UpdateLocation()
{
	Location base_location = *(this->base_location);
	LineCollider::ColliderBase::SetLocation
	(
		base_location - LineCollider::GetVector(LINE_START) + shift
	);

}

//-------------------------------------
// 当たった時の処理 当たった物の種類の記憶
//-------------------------------------
void Ray::HitFunction(ColliderBase* collider)
{
	int collider_type = collider->GetColliderType();

	bool is_exist = false;
	for (ColliderBase* hit_collider : hit_colliders)
	{
		if (hit_collider == collider)is_exist = true;
	}
	if (!is_exist)
	{
		hit_colliders.push_back(collider);
	}
}

//----------------------------------------------
// 当たっているコリダーを探す
//----------------------------------------------
const ColliderBase* Ray::SearchCollider(COLLIDER collider_type)const
{
	for (ColliderBase* hit_collider : hit_colliders)
	{
		if ((int)collider_type == hit_collider->GetColliderType())
		{
			return hit_collider;
		}
	}

	return nullptr;
}