#pragma once
#include"define.h"

#include"StageBuillder/Debug.h"
#include"DxLib.h"

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

#ifdef SHOW_COLLISION
	void DrawCollision()const
	{
		float x1 = location.x;
		float y1 = location.y;
	
		float x2 = location.x + area.width;
		float y2 = location.y + area.height;
		DrawBoxAA(x1, y1, x2, y2, 0xE9FF00, FALSE, 3);
	}
#endif
};