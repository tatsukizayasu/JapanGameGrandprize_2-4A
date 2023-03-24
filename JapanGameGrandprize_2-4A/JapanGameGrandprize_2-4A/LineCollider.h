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

	//2つのベクトルのなす角が鋭角かどうかを求める
	bool CheckIsAcute(Location vector1, Location vector2)const
	{
		bool is_acute = false;

		float vec_a = powf(powf(vector1.x, 2.0) + powf(vector1.y, 2.0), 0.5);
		float vec_b = powf(powf(vector2.x, 2.0) + powf(vector2.y, 2.0), 0.5);

		float inner_product = vector1.x * vector2.x + vector1.y * vector2.y;

		if (inner_product >= 0)
		{
			is_acute = true;
		}

		return is_acute;
	}

	//受け取ったベクターのスカラを返す
	float MakeScalar(Location vector)const
	{
		float scalar;

		scalar = powf((vector.x * vector.x) + (vector.y * vector.y), 0.5);

		return scalar;
	}

	//引数１から引数２に対する外積を返す
	float MakeCrossProduct(Location vector1, Location vector2)const
	{
		float cross_product;

		cross_product = (vector1.x * vector2.y) - (vector1.y * vector2.x);

		return cross_product;
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