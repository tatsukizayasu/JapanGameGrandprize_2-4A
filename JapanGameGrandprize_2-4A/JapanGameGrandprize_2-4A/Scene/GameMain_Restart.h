#pragma once
#include "AbstractScene.h"

class Pouch;

class GameMain_Restart : public AbstractScene
{
private:
	int now_graph;
	short stage_num;
	unsigned int old_element_volume[7];
	Pouch* old_pouch;

public:
	//コンストラクタ
	GameMain_Restart() = default;
	GameMain_Restart(short stage_num, int now_graph, unsigned int old_element_volume[7], Pouch* old_pouch);
	~GameMain_Restart();

	AbstractScene* Update() override;

	void Draw() const override;
};

