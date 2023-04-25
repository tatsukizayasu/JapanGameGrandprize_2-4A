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
ObjectBase::ObjectBase(Location pivot, ColliderBase* p_collider, const char* texture_name)
{
	this->texture_name = texture_name;
	TextureContainer* instance_texture = TextureContainer::GetInstance();
	image = instance_texture->GetTexture(texture_name);

	this->pivot = new SphereCollider(pivot);
	
	int class_type = p_collider->GetColliderType();
	switch (class_type)
	{
	case (int)COLLIDER::MAP_CHIP:
		collider = new BoxCollider(*static_cast<BoxCollider*>(p_collider));
		break;
	case (int)COLLIDER::SPHERE:
		collider = new SphereCollider(*static_cast<SphereCollider*>(p_collider));
		break;
	case (int)COLLIDER::BOX:
		collider = new BoxCollider(*static_cast<BoxCollider*>(p_collider));
		break;
	case (int)COLLIDER::LINE:
		collider = new LineCollider(*static_cast<LineCollider*>(p_collider));
		break;
	case (int)COLLIDER::POLY_LINE:
		collider = new PolyLine(*static_cast<PolyLine*>(p_collider));
		break;

	default:
		break;
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

}

//-----------------------------------
// 当たり判定の描画
//-----------------------------------
void ObjectBase::DrawCollider()const
{

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
