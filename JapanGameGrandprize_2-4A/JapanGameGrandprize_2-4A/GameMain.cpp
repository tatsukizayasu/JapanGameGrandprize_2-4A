#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"
#include"EnemySlime.h"
#include"EnemyGhost.h"
#include"Harpy.h"
#include "BULLET.h"
#include "Mage.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	stage = new Stage();
	player = new Player(stage);
	stage->SetPlayer(player);
	enemy = new EnemyBase * [4];
	enemy[0] = new Undead();
	enemy[1] = new EnemySlime();
	enemy[2] = new EnemyGhost();
	enemy[3] = new Mage();
	camera_work = new CameraWork(0, 800, player, stage);
	item_controller = new ItemController();

	bullet_manager = BulletManager::GetInstance();

	input_margin = 0;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
GameMain::~GameMain()
{
	delete player;
	delete stage;

	for (int i = 0; i < 3; i++)
	{
		delete enemy[i];
	}

	delete[] enemy;
	delete camera_work;
	delete bullet_manager;
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
	BulletBase** player_bullet;
	player_bullet = player->GetBullet();

	bullet_manager->Update(stage);

	EnemyBulletBase** enemy_bullet;
	enemy_bullet = bullet_manager->GetEnemyBullets();

	for (int i = 0; i < 4; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player,stage);

			//エネミーの攻撃
			if (enemy[i]->GetState() == ENEMY_STATE::ATTACK)
			{
				if (player->HitBox(enemy[i]))
				{
					player->HpDamage(enemy[i]->Hit());
				}
			}

			//プレイヤーの弾との当たり判定
			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (player_bullet[j] == nullptr)
				{
					break;
				}

				if (player_bullet[j]->HitBox(enemy[i]))
				{
					enemy[i]->HitBullet(player_bullet[j]);
					delete player_bullet[j];
					player_bullet[j] = nullptr;
					player->SortBullet(j);
				}
			}

			if (enemy[i]->GetCanDelete()) //エネミーの削除
			{
				item_controller->SpawnItem(enemy[i]);
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	//敵の弾とプレイヤーとの当たり判定
	if (enemy_bullet != nullptr)
	{
		for (int i = 0; i < bullet_manager->EnemyGetBulletMax(); i++)
		{
			if (enemy_bullet[i] == nullptr)
			{
				break;
			}
			if (enemy_bullet[i]->HitBox(player))
			{
				player->HpDamage(bullet_manager->Hit(i));
				bullet_manager->DeleteEnemyBullet(enemy_bullet[i]);
				i--;
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

	stage->Draw();
	item_controller->Draw();

	player->Draw();

	for (int i = 0; i < 4; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	bullet_manager->Draw();

}