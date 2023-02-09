#include "DxLib.h"
#include "GameMain.h"
#include "Title.h"
#include "CameraWork.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();
	camera_work = new CameraWork(100,300);

	input_margin = 0;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
GameMain::~GameMain()
{
	delete player;
	delete stage;
	delete camera_work;
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* GameMain::Update()
{
	//シーン切り替えテスト		デバック
	if (CheckHitKey(KEY_INPUT_Z) && input_margin >= 30) 
	{
		input_margin = 0;
		return new Title();
	}

	if (input_margin < 30) 
	{
		input_margin++;
	}

	camera_work->Update();
	player->Update();
	stage->Update();
	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void GameMain::Draw()const
{
	//背景
	SetBackgroundColor(149, 249, 253);

	player->Draw();
	stage->Draw();
}