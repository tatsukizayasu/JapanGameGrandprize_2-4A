#pragma once
#include "Define.h"
#include "Stage/StageBuilder/Debug.h"
#include "ColliderBase.h"

#define _USE_MATH_DEFINES
#include <math.h>


#define LINE_START 0
#define LINE_END 1

class LineCollider_t :public ColliderBase
{
private:

	Location GetMiddlePoint(Location point1, Location point2)const
	{
		Location middle_point;
		middle_point.x = (point1.x + point2.x) / 2;
		middle_point.y = (point1.y + point2.y) / 2;

		return middle_point;
	}
	void Relativize()
	{
		vector[LINE_START].x = vector[LINE_START].x - location.x;
		vector[LINE_START].y = vector[LINE_START].y - location.y;

		vector[LINE_END].x = vector[LINE_END].x - location.x;
		vector[LINE_END].y = vector[LINE_END].y - location.y;
	}
	Location MakeTip(int index)const
	{
		//線分の端の絶対座標を計算する
		Location tip;
		tip.x = location.x + vector[index].x;
		tip.y = location.y + vector[index].y;

		return tip;
	}
public:
	LineCollider_t();
	LineCollider_t(Location point1, Location point2);
	~LineCollider_t();

	//描画
	virtual void Draw()const;

	//点との当たり判定
	bool HitDot(Location point)const;

	//SphereColliderとの当たり判定
	bool HitSphere(const class SphereCollider* sphere_collider)const override;

	//BoxColliderとの当たり判定
	bool HitBox(const class BoxCollider* box_collider)const override;

	//LineColliderとの当たり判定
	bool HitLine(const class LineCollider_t* line_collider)const override;

	//線の端の座標の取得
	Location GetLocation(int i)const;

	//始点、終点座標の設定
	void SetLocation(Location location, int i);



protected:
	Location vector[2];	//中心から線の端の座標までのベクター(0:始点,1:終点)
};

class LineCollider
{
protected:

	Location location[2];	//線の端の座標(0:始点,1:終点)
public:

	//SphereColliderとの当たり判定
	bool HitSphere(class SphereCollider* sphere_collider);

	//BoxColliderとの当たり判定
	bool HitBox(class BoxCollider* box_collider);

	//LineColliderとの当たり判定
	bool HitLine(LineCollider* line_collider);

	//線の端の座標の取得
	Location GetLocation(int i)const;

	//中心座標の設定
	void SetLocation(Location location, int i);

#ifdef _SHOW_COLLISION
	void DrawCollision()const
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawLineAA(location[0].x, location[0].y, location[1].x, location[1].y, 0xE9FF00);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//DrawCircle
	}
#endif
};