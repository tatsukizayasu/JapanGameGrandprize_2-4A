#pragma once
#include"define.h"

#include"Stage/StageBuilder/Debug.h"
#include"DxLib.h"
#include "ColliderBase.h"

class BoxCollider : public ColliderBase
{
protected:
	
	Area area; //範囲
	Area margin_area;	//当たり判定範囲の誤差修正

public:

	//SphereColliderとの当たり判定
	bool HitSphere(const class SphereCollider* sphere_collider) const override;

	//BoxColliderとの当たり判定
	bool HitBox(const class BoxCollider* box_collider) const override;

	//LineColliderとの当たり判定
	bool HitLine(const class LineCollider* line_collider) const override;
	
	//中心座標の取得
	Location GetLocation()const;

	//半径の取得
	Area GetArea()const;

	//中心座標の設定
	void SetLocation(Location location);

};