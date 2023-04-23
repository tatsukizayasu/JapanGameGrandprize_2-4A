#include "GameMain.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "PadInput.h"
#include "Undead.h"
#include "EnemySlime.h"
#include "EnemyGhost.h"
#include "Harpy.h"
#include "BULLET.h"
#include "Mage.h"
#include "Wyvern.h"
#include "Torrent.h"
#include "EnemySlimeBoss.h"
#include"Dragon.h"
#include "DotByDot.h"
#include <math.h>
#include "GameOver.h"
#include "GameClear.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain(short stage_num)
{
#undef DOT_BY_DOT
	//背景画像読み込み
	background_image[0] = LoadGraph("Images/Scene/Stage/1/BackImage1.png");
	background_image[1] = LoadGraph("Images/Scene/Stage/1/BackImage2.png");
#ifdef _DEBUG

#else
	pause = new Pause();
#endif
	enemy_spawn_volume = 0;
	this->stage_num = stage_num;
	stage = new Stage(stage_num);
	player = new Player(stage);
	stage->SetPlayer(player);

	EnemyBase::CreateLogFont();

	SpawnEnemy();
	camera_work = new CameraWork(0, 800, player, stage);
	stage->SetCameraWork(camera_work);
	item_controller = new ItemController();
	
	bullet_manager = BulletManager::GetInstance();

	input_margin = 0;
	is_spawn_boss = false;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
GameMain::~GameMain()
{

	delete camera_work;
#ifdef _DEBUG

#else
	delete pause;
#endif
	delete player;
	delete stage;

	EnemyBase::DeleteLogFont();
	for (int i = 0; i < enemy_spawn_volume; i++)
	{
		delete enemy[i];
	}
	delete[] enemy;

	delete item_controller;
	delete bullet_manager;
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* GameMain::Update()
{
#ifdef _DEBUG

#else
	pause->Update();
	if (pause->GetNextMenu() == TRUE) { return new GameMain(); }
	if (pause->IsPause() == TRUE) { return this; }
#endif


#ifdef _DEBUG
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		return new DotByDot();
	}
#endif



	camera_work->Update();
	player->Update();
	stage->Update(player);



	if (EnemyUpdate() == true)
	{
		return new GameClear(stage_num);
	}
	item_controller->Update(player);
	if (player->GetState() == PLAYER_STATE::DEATH)
	{
		return new GameOver(stage_num);
	}

	return this;
}

//-----------------------------------
//エネミーの生成
//-----------------------------------
void GameMain::SpawnEnemy()
{

	vector<ENEMY_LOCATION> spawn;
	spawn = stage->GetEnemy_SpawnLocation();

	enemy_spawn_volume = spawn.size();
	enemy = new EnemyBase * [enemy_spawn_volume];
	int i;
	for (i = 0; i < enemy_spawn_volume; i++)
	{
		switch (static_cast<ENEMY_KIND>(spawn[i].id))
		{
		case ENEMY_KIND::SLIME: //スライムの生成
			enemy[i] = new EnemySlime(spawn[i].location);
			break;
		case ENEMY_KIND::UNDEAD:	//アンデットの生成
			enemy[i] = new Undead(spawn[i].location);
			break;
		case ENEMY_KIND::HARPY:		//ハーピーの生成
			enemy[i] = new Harpy(spawn[i].location);
			break;
		case ENEMY_KIND::MAGE:		//メイジの生成
			enemy[i] = new Mage(spawn[i].location);
			break;
		case ENEMY_KIND::GHOST:		//ゴーストの生成
			enemy[i] = new EnemyGhost(spawn[i].location);
			break;
		case ENEMY_KIND::WYVERN:	//ワイバーンの生成
			enemy[i] = new Wyvern(spawn[i].location);
			break;
		case ENEMY_KIND::SLIME_BOSS://スライムボスの生成
			enemy[i] = nullptr;
			break;
		case ENEMY_KIND::TORRENT:	//トレントボスの生成
			enemy[i] = new Torrent(spawn[i].location);
			break;
		case ENEMY_KIND::KRAKEN:	//クラーケンボスの生成
			break;
		case ENEMY_KIND::DRAGON:	//ドラゴンボスの生成
			enemy[i] = new Dragon(spawn[i].location);
			break;
		case ENEMY_KIND::END_BOSS:	//ラスボスの生成
			break;
		case ENEMY_KIND::NONE:
		default:
			enemy[i] = nullptr;
			break;
		}
	}
}

//-----------------------------------
// エネミーの更新処理
//-----------------------------------
bool GameMain::EnemyUpdate()
{
	//クリア判定用フラグ
	bool is_clear = false;

	//プレイヤーがボスエリアに入った際、ボスを出現させる
	if (camera_work->GetCameraLock() == true && is_spawn_boss == false)
	{
		vector<ENEMY_LOCATION> spawn;
		spawn = stage->GetEnemy_SpawnLocation();

		enemy_spawn_volume = spawn.size();
		int boss_index;
		for (int i = 0; i < enemy_spawn_volume; i++)
		{
			if (static_cast<short>(ENEMY_KIND::SLIME_BOSS) <= spawn[i].id)
			{
				if (enemy[i] == nullptr)
				{
					enemy[i] = new EnemySlimeBoss(spawn[i].location);
					is_spawn_boss = true;
					break;
				}
			}
		}
	}

	BulletBase** player_bullet;
	player_bullet = player->GetBullet();

	for (int i = 0; i < enemy_spawn_volume; i++)
	{
		if (enemy[i] != nullptr)
		{
				enemy[i]->Update(player, stage);

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

				if(enemy[i]->HitSphere(player_bullet[j]))
				{
					enemy[i]->HitBullet(player_bullet[j]);
					delete player_bullet[j];
					player_bullet[j] = nullptr;
					player->SortBullet(j);
					j--;
				}
			}

			if (enemy[i]->GetCanDelete()) //エネミーの削除
			{
				if (ENEMY_KIND::SLIME_BOSS == enemy[i]->GetEnemyKind())
				{
					is_clear = true;
				}

				item_controller->SpawnItem(enemy[i]);
				delete enemy[i];
				enemy[i] = nullptr;
				i--;
			}
		}
	}

	bullet_manager->Update(stage);

	EnemyBulletBase** enemy_bullet;
	enemy_bullet = bullet_manager->GetEnemyBullets();

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
				player->HpDamage(bullet_manager->HitEnemyBullet(i));
				bullet_manager->DeleteEnemyBullet(enemy_bullet[i]);
				i--;
			}
		}
	}

	EnemyBulletBase** enemy_nuts;
	enemy_nuts = bullet_manager->GetEnemyNuts();

	if (enemy_nuts != nullptr) //木の実との当たり判定
	{
		for (int i = 0; i < bullet_manager->EnemyGetNutsMax(); i++)
		{
			if (enemy_nuts[i] == nullptr)
			{
				break;
			}

			if (enemy_nuts[i]->HitBox(player))
			{
				player->HpDamage(bullet_manager->HitEnemyNuts(i));
				bullet_manager->DeleteEnemyNuts(enemy_nuts[i]);
				i--;
			}

			if (enemy_nuts[i] == nullptr)
			{
				break;
			}

			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (player_bullet[j] == nullptr)
				{
					break;
				}

				if (player_bullet[j]->HitSphere(enemy_nuts[i]))
				{
					bullet_manager->DeleteEnemyNuts(enemy_nuts[i]);
					i--;

					delete player_bullet[j];
					player_bullet[j] = nullptr;
					player->SortBullet(j);
					j--;
				}
			}
		}
	}

	return is_clear;
}

//-----------------------------------
// 描画
//-----------------------------------
void GameMain::Draw()const
{
	////背景	描画
	// DrawGraph(0, 0, background_image, FALSE);
	Location camera_work = CameraWork::GetCamera();
	
	DrawGraphF(-fmodf(camera_work.x * 0.8, SCREEN_WIDTH), 0, background_image[1], TRUE);
	DrawGraphF(-fmodf(camera_work.x * 0.8, SCREEN_WIDTH) + SCREEN_WIDTH, 0, background_image[1], TRUE);

	DrawGraphF(-fmodf(camera_work.x, SCREEN_WIDTH), 0, background_image[0], TRUE);
	DrawGraphF(-fmodf(camera_work.x, SCREEN_WIDTH) + SCREEN_WIDTH, 0, background_image[0], TRUE);

	stage->Draw();
	item_controller->Draw();

	player->Draw();

	for (int i = 0; i < enemy_spawn_volume; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	bullet_manager->Draw();

	player->PouchDraw();
#ifdef _DEBUG

#else
	//ポーズ		描画
	if (pause->IsPause() == true) { pause->Draw(); }
#endif
}