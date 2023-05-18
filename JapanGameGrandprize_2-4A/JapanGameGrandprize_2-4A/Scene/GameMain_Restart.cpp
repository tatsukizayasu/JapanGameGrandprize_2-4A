#include "GameMain_Restart.h"
#include "GameMain.h"
#include "../Pouch.h"
#include "DxLib.h"

GameMain_Restart::GameMain_Restart(short stage_num, int now_graph, unsigned int old_element_volume[PLAYER_ELEMENT], Pouch* old_pouch) : AbstractScene() {
	this->stage_num = stage_num;
	this->now_graph = now_graph;
	
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		this->old_element_volume[i] = old_element_volume[i];
	}

	this->old_pouch = old_pouch;
}

GameMain_Restart::~GameMain_Restart()
{
	DeleteGraph(now_graph);

}

AbstractScene* GameMain_Restart::Update() {
	return new GameMain(stage_num, old_element_volume, old_pouch);
	return this;
}


void GameMain_Restart::Draw()const {
	DrawGraph(0, 0, now_graph, FALSE);
}