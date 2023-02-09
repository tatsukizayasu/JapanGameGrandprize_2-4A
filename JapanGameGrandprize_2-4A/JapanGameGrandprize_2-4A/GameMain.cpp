#include "DxLib.h"
#include "GameMain.h"
#include "Title.h"

GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();

	input_margin = 0;
}

GameMain::~GameMain()
{
	delete stage;
}

AbstractScene* GameMain::Update()
{
	//シーン切り替えテスト		デバック
	if (CheckHitKey(KEY_INPUT_Z) && input_margin >= 30) {
		input_margin = 0;
		return new Title();
	}

	if (input_margin < 30) {
		input_margin++;
	}

	player->Update();
	stage->Update();
	return this;
}

void GameMain::Draw()const
{
	//背景
	SetBackgroundColor(149, 249, 253);

	player->Draw();
	stage->Draw();
}

