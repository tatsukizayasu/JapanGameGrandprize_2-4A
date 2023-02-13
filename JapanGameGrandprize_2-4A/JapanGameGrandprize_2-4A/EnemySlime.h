#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"

enum DIRECTION
{
	left = -1,
	right = 1
};

class EnemySlime : public EnemyBase , public BoxCollider
{
private:
	int color;
	int a;
	float old_location_x, old_location_y;
	int direction;
public:
	EnemySlime();
	EnemySlime(float x,float y, float height, float width);
	~EnemySlime() {};

	//描画以外の更新を実行
	virtual void Update()override;
	//描画
	virtual void Draw()const override;

	void Hit();
	void HitStage();
	void Attack(BoxCollider* boxcollider);
};
