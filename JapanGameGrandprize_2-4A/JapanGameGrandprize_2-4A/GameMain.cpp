#include "DxLib.h"
#include "GameMain.h"

GameMain::GameMain()
{
	player = new Player();
}

GameMain::~GameMain()
{
	
}

AbstractScene* GameMain::Update()
{
	player->Update();
	return this;
}

void GameMain::Draw()const
{
	player->Draw();
}

