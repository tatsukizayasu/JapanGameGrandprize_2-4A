#include "DxLib.h"
#include "GameMain.h"

GameMain::GameMain()
{
	stage = new Stage();
}

GameMain::~GameMain()
{
	delete stage;
}

AbstractScene* GameMain::Update()
{
	stage->Update();
	return this;
}

void GameMain::Draw()const
{
	stage->Draw();
}

