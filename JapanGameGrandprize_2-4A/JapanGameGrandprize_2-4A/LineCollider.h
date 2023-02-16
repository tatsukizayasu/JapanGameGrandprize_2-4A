#pragma once
#include "Define.h"
#include "Stage/StageBuilder/StageBuilder.h"
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