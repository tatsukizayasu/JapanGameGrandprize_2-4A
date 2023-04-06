#pragma once
#include "Define.h"
#include "Stage/StageBuilder/Debug.h"
#include "ColliderBase.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define LINE_START 0
#define LINE_END 1

class LineCollider :public ColliderBase
{
private:

	//中点を返す
	Location GetMiddlePoint()const
	{
		Location middle_point;
		middle_point.x = (vector[LINE_START].x + vector[LINE_END].x) / 2;
		middle_point.y = (vector[LINE_START].y + vector[LINE_END].y) / 2;

		return middle_point;
	}

	//座標を中心座標からのベクターに相対化する
	void Relativize()
	{
		vector[LINE_START].x = vector[LINE_START].x - location.x;
		vector[LINE_START].y = vector[LINE_START].y - location.y;

		vector[LINE_END].x = vector[LINE_END].x - location.x;
		vector[LINE_END].y = vector[LINE_END].y - location.y;
	}

	//線分の端の絶対座標を返す
	Location MakeTip(int index)const
	{
		//線分の端の絶対座標を計算する
		Location tip;
		tip.x = location.x + vector[index].x;
		tip.y = location.y + vector[index].y;

		return tip;
	}


public:
	LineCollider();
	LineCollider(Location point1, Location point2);
	~LineCollider();

	//描画
	virtual void Draw()const;

	//点との当たり判定
	bool HitDot(Location point)const;

	//SphereColliderとの当たり判定
	bool HitSphere(const class SphereCollider* sphere_collider)const override;

	//BoxColliderとの当たり判定
	bool HitBox(const class BoxCollider* box_collider)const override;

	//LineColliderとの当たり判定
	bool HitLine(const class LineCollider* line_collider)const override;

	ColliderBase* Copy()const override { return new LineCollider(*this); }

	//線の端の座標の取得
	Location GetLocation(int i)const;

	//始点、終点座標の設定
	void SetLocation(Location location, int i);


	//線分を対角線とした矩形の左上の座標を返す
	Location GetMin()const
	{
		Location vector_min = {};
		float x;
		float y;

		if (GetLocation(LINE_START).x < GetLocation(LINE_END).x)
		{
			x = GetLocation(LINE_START).x;
		}
		else
		{
			x = GetLocation(LINE_END).x;
		}

		if (GetLocation(LINE_START).y < GetLocation(LINE_END).y)
		{
			y = GetLocation(LINE_START).y;
		}
		else
		{
			y = GetLocation(LINE_END).y;
		}

		vector_min = { x,y };

		return vector_min;
	}

	//線分を対角線とした矩形の右下の座標を返す
	Location GetMax()const
	{
		Location vector_max{};
		float x;
		float y;

		if (GetLocation(LINE_START).x > GetLocation(LINE_END).x)
		{
			x = GetLocation(LINE_START).x;
		}
		else
		{
			x = GetLocation(LINE_END).x;
		}

		if (GetLocation(LINE_START).y > GetLocation(LINE_END).y)
		{
			y = GetLocation(LINE_START).y;
		}
		else
		{
			y = GetLocation(LINE_END).y;
		}

		vector_max = { x,y };

		return vector_max;
	}

protected:

	Location vector[2];	//中心から線の端の座標までのベクター(0:始点,1:終点)
};