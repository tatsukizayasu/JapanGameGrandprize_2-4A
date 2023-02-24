#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"
#include"EnemySlime.h"
#include"EnemyGhost.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	stage = new Stage();
	player = new Player(stage);
	enemy = new EnemyBase * [3];
	enemy[0] = new Undead(player);
	enemy[1] = new EnemySlime();
	enemy[2] = new EnemyGhost();
	camera_work = new CameraWork(0, 0, player, stage);
	item_controller = new ItemController();

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
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) && input_margin >= 30)
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
	stage->Update(player);

	EnemyUpdate();
	item_controller->Update(player);

	return this;
}

//-----------------------------------
// エネミーの更新処理
//-----------------------------------
void GameMain::EnemyUpdate()
{
	for (int i = 0; i < 3; i++)
	{

		if (enemy != nullptr)
		{
			enemy[i]->Update();

		switch (enemy->GetState())
		{
		case ENEMY_STATE::IDOL:
			enemy->Idol();
			break;
		case ENEMY_STATE::MOVE:
			enemy->Move(player->GetLocation());
			break;
		case ENEMY_STATE::ATTACK:
			enemy->Attack(player);
			break;
		case ENEMY_STATE::DEATH:
			enemy->Death();
			break;
		default:
			break;
		}

		if (enemy->GetCanDelete())
		{

		}

		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (player->GetBullet(i) != nullptr)
			{
				enemy->HitBullet(player->GetBullet(i));
			}
		}
	}

	}

}

//-----------------------------------
// 描画
//-----------------------------------
void GameMain::Draw()const
{
	//背景
	SetBackgroundColor(149, 249, 253);

	item_controller->Draw();
	player->Draw();
	stage->Draw();
	for (int i = 0; i < 3; i++)
	{
		if (enemy != nullptr)
		{
			enemy[i]->Draw();
		}
	}
}