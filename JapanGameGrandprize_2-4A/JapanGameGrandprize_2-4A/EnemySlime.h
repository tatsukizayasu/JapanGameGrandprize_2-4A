#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"

class EnemySlime : public EnemyBase , public BoxCollider
{
private:
	int slime_x;
	int slime_y;

	int draw_x;
	int draw_y;

	int a;
public:
	EnemySlime();
	~EnemySlime() {};

	//描画以外の更新を実行
	virtual void Update()override;
	//描画
	virtual void Draw()const override;

	//void SetSlimeX(int a);
	//int SetSlimeX();*/

	void Hit();
};
