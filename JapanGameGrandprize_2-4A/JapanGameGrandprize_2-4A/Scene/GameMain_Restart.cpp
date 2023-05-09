#include "GameMain_Restart.h"
#include "GameMain.h"
#include "DxLib.h"

GameMain_Restart::GameMain_Restart(short stage_num, int now_graph) : AbstractScene() {
	this->stage_num = stage_num;
	this->now_graph = now_graph;
}

GameMain_Restart::~GameMain_Restart()
{
	DeleteGraph(now_graph);

}

AbstractScene* GameMain_Restart::Update() {
		return new GameMain(stage_num);
}


void GameMain_Restart::Draw()const {
	DrawGraph(0, 0, now_graph, FALSE);
}