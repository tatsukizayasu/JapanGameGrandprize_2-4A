#pragma once
#include"define.h"


class BoxCollider
{
protected:
	Location location;	//中心座標
	Area area; //範囲
public:

	//SphereColliderとの当たり判定
	bool HitSphere(class SphereCollider* sphere_collider);

	//BoxColliderとの当たり判定
	bool HitBox(BoxCollider* box_collider);
	
	//中心座標の取得
	Location GetLocation()const;

	//半径の取得
	Area GetArea()const;

	//中心座標の設定
	void SetLocation(Location location);
};