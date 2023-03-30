#include "ObjectBase.h"
#include "../../BoxCollider.h"

//--------------------------------
// コンストラクタ
//--------------------------------
ObjectBase::ObjectBase()
{
	pivot = { 640,360 };
}

//--------------------------------
// コンストラクタ
//--------------------------------
ObjectBase::ObjectBase(Location pivot)
{
	this->pivot = pivot;
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
	DrawRotaGraphF(pivot.x, pivot.y, 1.0, 0, image, TRUE, is_reverse);

	collider->Draw();
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
