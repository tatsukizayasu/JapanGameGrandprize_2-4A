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
ObjectBase::ObjectBase(Location pivot)
{
	this->pivot = new SphereCollider(pivot);
	image = LoadGraph("images/Stage/yuka_1.png");

	collider =  new BoxCollider({ 640,360 }, { 100,100 });

	vector = collider->GetLocation() - pivot;
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
	Location draw_pos = pivot->GetLocation() + CameraWork::GetCamera();

	DrawRotaGraphF(draw_pos.x,draw_pos.y,1.0, 0, image, TRUE, is_reverse);

#ifdef _STAGE_BUILDER
	DrawCircleAA(draw_pos.x, draw_pos.y, 5, 10, 0xFF0000, TRUE);
	collider->Draw();
#endif
}

//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------


//--------------------------------
// 
//--------------------------------
