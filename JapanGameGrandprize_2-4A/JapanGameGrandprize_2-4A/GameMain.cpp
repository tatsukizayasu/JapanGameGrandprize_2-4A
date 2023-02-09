#include "DxLib.h"
#include "GameMain.h"

GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();
}

GameMain::~GameMain()
{
	delete stage;
}

AbstractScene* GameMain::Update()
{

	player->Update();
	stage->Update();
	return this;
}

void GameMain::Draw()const
{
	//”wŒi
	SetBackgroundColor(149, 249, 253);

	player->Draw();
	stage->Draw();
}

