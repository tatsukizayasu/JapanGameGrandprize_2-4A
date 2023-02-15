#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"

#define _DEBUG

//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	stage = new Stage();
	player = new Player(stage);
	enemy = new Undead();
	camera_work = new CameraWork(0,0);

	input_margin = 0;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
GameMain::~GameMain()
{
	delete player;
	delete stage;
	delete enemy;
	delete camera_work;
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* GameMain::Update()
{
#ifdef _DEBUG
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
#endif

	camera_work->Update();
	player->Update();
	stage->Update();
	
	EnemyUpdate();

	return this;
}

//-----------------------------------
// エネミーの更新処理
//-----------------------------------
void GameMain::EnemyUpdate()
{
	enemy->Update();

	switch (enemy->GetEnemyKind())
	{
		case ENEMY_KIND::SLIME:		//スライム
			break;
		case ENEMY_KIND::UNDEAD:	//アンデット
			Undead* undead;
			undead = dynamic_cast<Undead*>(enemy);
			undead->DistancePlayer(player);
			break;
		case ENEMY_KIND::HARPY:		//ハーピィ
			break;
		case ENEMY_KIND::MAGE:		//メイジ
			break;
		case ENEMY_KIND::GHOST:		//ゴースト
			break;
		case ENEMY_KIND::WYVERN:	//ワイバーン
			break;
		case ENEMY_KIND::KING_SLIME://スライムキング
			break;
		case ENEMY_KIND::TORRENT:	//トレント
			break;
		case ENEMY_KIND::GARGOYLE:	//ガーゴイル
			break;
		case ENEMY_KIND::DRAGON:	//ドラゴン
			break;
		case ENEMY_KIND::END_BOSS:	//ラスボス
			break;
		case ENEMY_KIND::NONE:
			break;
	default:
		break;
	}

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
	enemy->Draw();
}

