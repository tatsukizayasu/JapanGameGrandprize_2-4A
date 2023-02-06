#pragma once
#include"EnemyBase.h"

class EnemySlime : public EnemyBase
{
private:
	int slime_x;
	int slime_y;

public:
	EnemySlime();

	//描画以外の更新を実行
	virtual void Update()override;
	//描画
	virtual void Draw()const override ;


};