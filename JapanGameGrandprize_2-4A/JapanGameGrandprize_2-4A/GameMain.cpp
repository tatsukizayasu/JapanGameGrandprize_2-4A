#include "DxLib.h"
#include "GameMain.h"
#include "Undead.h"

GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();
	enemy = new Undead();

}

GameMain::~GameMain()
{
	delete stage;
	delete player;
	delete enemy;
}

AbstractScene* GameMain::Update()
{

	player->Update();
	stage->Update();
	enemy->Update();

	Undead* a = dynamic_cast<Undead*>(enemy);
	a->DistancePlayer(player);

	return this;
}

void GameMain::Draw()const
{
	//”wŒi
	SetBackgroundColor(149, 249, 253);

	player->Draw();
	stage->Draw();
	enemy->Draw();
}

