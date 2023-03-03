#pragma once
#include"define.h"

#include"Stage/StageBuilder/Debug.h"
#include"DxLib.h"
#include "ColliderBase.h"

class BoxCollider : public ColliderBase
{
protected:
	
	Area area; //範囲
public:

	//SphereColliderとの当たり判定
	bool HitSphere(const class SphereCollider* sphere_collider) const;

	//BoxColliderとの当たり判定
	bool HitBox(const BoxCollider* box_collider) const;

	//LineColliderとの当たり判定
	bool HitLine(const class LineCollider* line_collider) const;
	
	//中心座標の取得
	Location GetLocation()const;

	//半径の取得
	Area GetArea()const;

	//中心座標の設定
	void SetLocation(Location location);

#ifdef _SHOW_COLLISION
	void DrawCollision()const
	{
		float x1 = location.x - (area.width / 2);
		float y1 = location.y - (area.height / 2);
	
		float x2 = x1 + area.width;
		float y2 = y1 + area.height;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawBoxAA(x1, y1, x2, y2, 0xE9FF00, FALSE, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
#endif
};