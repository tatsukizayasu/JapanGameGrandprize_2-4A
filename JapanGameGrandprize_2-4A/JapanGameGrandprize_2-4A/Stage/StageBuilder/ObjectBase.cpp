#include "ObjectBase.h"
#include "../../BoxCollider.h"
#include "../CameraWork.h"

//--------------------------------
// コンストラクタ
//--------------------------------
ObjectBase::ObjectBase()
{
	pivot = new SphereCollider({ 640,360 });
}

//--------------------------------
// コンストラクタ
//--------------------------------
ObjectBase::ObjectBase(Location pivot, ColliderBase* p_collider)
{
	this->pivot = new SphereCollider(pivot);
	image = LoadGraph("images/Stage/yuka_1.png");
	

	p_collider = dynamic_cast<BoxCollider*>(p_collider);
	if (p_collider)
	{
		collider = new BoxCollider(*dynamic_cast<BoxCollider*>(p_collider));
	}

	p_collider = dynamic_cast<SphereCollider*>(p_collider);
	if (p_collider)
	{
		collider = new SphereCollider(*dynamic_cast<SphereCollider*>(p_collider));
	}

	p_collider = dynamic_cast<LineCollider*>(p_collider);
	if (p_collider)
	{
		collider = new LineCollider(*dynamic_cast<LineCollider*>(p_collider));
	}

	p_collider = dynamic_cast<PolyLine*>(p_collider);
	if (p_collider)
	{
		collider = new PolyLine(*dynamic_cast<PolyLine*>(p_collider));
	}


	vector = collider->GetLocation() - pivot;
	old_location = collider->GetLocation();
	is_reverse = FALSE;
	
}

//--------------------------------
// デストラクタ
//--------------------------------
ObjectBase::~ObjectBase()
{
	
}

//--------------------------------
// 描画
//--------------------------------
void ObjectBase::Draw()const
{
	Location draw_pos = pivot->GetLocation() - CameraWork::GetCamera();

	DrawRotaGraphF(draw_pos.x,draw_pos.y,1.0, 0, image, TRUE, is_reverse);

	DrawLineAA(pivot->GetLocation().x - CameraWork::GetCamera().x, pivot->GetLocation().y - CameraWork::GetCamera().y,
		collider->GetLocation().x - CameraWork::GetCamera().x, collider->GetLocation().y - CameraWork::GetCamera().y, 0xFFFF00, 3);

#ifdef _STAGE_BUILDER
	pivot->Draw();
	collider->Draw();
#endif
}

//--------------------------------
// 当たり判定クラスの場所の更新
//--------------------------------
void ObjectBase::UpdateColliderPos()
{
	if (old_location != collider->GetLocation())
	{
		vector = collider->GetLocation() - pivot->GetLocation();
		old_location = collider->GetLocation();
	}
	else
	{
		collider->SetLocation(pivot->GetLocation() + vector);
		old_location = collider->GetLocation();
	}
}

//--------------------------------
// 当たり判定クラスのキャスト
//--------------------------------
void ObjectBase::ColliderCast(ColliderBase* p_collider)
{

}

//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------
