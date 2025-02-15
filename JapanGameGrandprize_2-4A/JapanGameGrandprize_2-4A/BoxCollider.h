#pragma once
#include"define.h"

#include"Stage/StageBuilder/Debug.h"
#include"DxLib.h"

#include "SphereCollider.h"
#include "LineCollider.h"
#include "ColliderBase.h"


class BoxCollider : public ColliderBase
{
protected:
	
	Area area; //範囲
	Area margin_area;	//当たり判定範囲の誤差修正
public:

	BoxCollider();
	BoxCollider(Location location, Area area);
	~BoxCollider();

	virtual void Draw()const;

	//SphereColliderとの当たり判定
	bool HitSphere(const class SphereCollider* sphere_collider) const override;

	//BoxColliderとの当たり判定
	bool HitBox(const class BoxCollider* box_collider) const override;

	//LineColliderとの当たり判定
	bool HitLine(const class LineCollider* line_collider) const override;

	//PolyLineとの当たり判定
	virtual bool HitPolyLine(const class PolyLine* poly_line)const override;

	ColliderBase* Copy()const override { return new BoxCollider(*this); }

	bool HitCheck(ColliderBase* collider)const;
	
	//中心座標の取得
	Location GetLocation()const;

	//半径の取得
	Area GetArea()const;

	//中心座標の設定
	virtual void SetLocation(Location location);

	//ゲームプレイ時に当たり判定をとる分には必要のないもの
	//ツール上でマウスとの当たり判定をとるために使用しています
#ifdef _STAGE_BUILDER
private:
	SphereCollider spheres[4];
	SphereCollider pivot;
	Location old_pos[4];

public:
	SphereCollider* GetSpheres() { return spheres; }
	SphereCollider* GetPivot() { return &pivot; }
	void UpdatePos();
#endif

};