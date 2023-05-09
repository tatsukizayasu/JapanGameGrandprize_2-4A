#include "Ray.h"

//------------------------------
// コンストラクタ
//------------------------------
Ray::Ray()
{
	int a=4;
	const int b = 5;
	int c = a + b;

}

//------------------------------
// コンストラクタ
//------------------------------
Ray::Ray(const Location* location):base_location(location)
{
	LineCollider::SetLocation(Location{ 0,0 }, LINE_START);
	LineCollider::SetLocation(Location{ 0,100 }, LINE_END);

	LineCollider::ColliderBase::SetLocation
	(
		*base_location - LineCollider::GetVector(LINE_START)
		)
}

//------------------------------
// デストラクタ
//------------------------------
Ray::~Ray()
{

}