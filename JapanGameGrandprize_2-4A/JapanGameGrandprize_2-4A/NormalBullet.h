#pragma once
#include "DxLib.h"
#include "BULLET.h"
#include "Define.h"
#include "SphereCollider.h"

#define PIXEL_MAX 4

class NormalBullet : public BulletBase
{
private:

	int Tick;
	float speed_x, speed_y[PIXEL_MAX];
	float dot_location_x[PIXEL_MAX], dot_location_y[PIXEL_MAX];
	Bullet_Effect Explosion[4];	//0:本弾　1:波動(発射時) 2:波動　3:軌跡
	Bullet_Effect Melt[2];		//0:本弾　1:軌跡
	Bullet_Effect Paralysis[2];	//0:本弾　1:軌跡
	Bullet_Effect Poison[2];	//0:本弾　1:軌跡
	Delete_Effect exp;
	Delete_Effect mel;
	Delete_Effect par;
	Delete_Effect poi;
public:

	NormalBullet();
	NormalBullet(float, float,bool,ChemicalFormulaParameter*);
	~NormalBullet() {}

	void Draw() const override;
	void Update(const Stage*) override;

	bool NormalBulletEfect();

	void Set_exp_Delete_flg(bool b, int x, int y);		//エネミーは当たった弾次第で呼び出すSetを分けてください
	void Set_mel_Delete_flg(bool b, int x, int y);		//当たった時にboolはtrue、当たった座標をx,yそれぞれ渡してほしいです
	void Set_poi_Delete_flg(bool b, int x, int y);		//trueを入れてくれたら着弾エフェクトが再生されるはずです
	void Set_par_Delete_flg(bool b, int x, int y);		//再生し終えたらNomalBullet側でfalseが入ります
	
	bool GetDelete_flg();								//trueをSetした後にエネミーはfalse待ちの状態にしてほしいです
														//falseが入った後にDeleteしてください
	int GetDamageParSecond();
};