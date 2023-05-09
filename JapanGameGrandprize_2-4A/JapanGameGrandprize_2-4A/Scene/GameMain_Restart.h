#pragma once
#include "AbstractScene.h"


class GameMain_Restart : public AbstractScene
{
private:
	int now_graph;
	short stage_num;

public:
	//コンストラクタ
	GameMain_Restart() = default;
	GameMain_Restart(short stage_num, int now_graph);
	~GameMain_Restart();

	AbstractScene* Update() override;

	void Draw() const override;
};

