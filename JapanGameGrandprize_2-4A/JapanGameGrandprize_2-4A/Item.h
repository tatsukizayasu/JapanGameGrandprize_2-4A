#pragma once
#include"SphereCollider.h"

class Item :
	public SphereCollider
{
private:
	int color; //色
public:
	//コンストラクタ
	Item();

	//更新
	void Update();

	//描画
	void Draw()const;
};

