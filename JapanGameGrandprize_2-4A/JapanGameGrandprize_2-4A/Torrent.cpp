#include "Torrent.h"
#include "DxLib.h"
#include "Player.h"
#include "Stage/Stage.h"
#include "TorrentBullet.h"
#include "TorrentNuts.h"
#include "BulletManager.h"
#include "CameraWork.h"

//移動速度
#define TORRENT_SPEED 4

//タックルのダメージ
#define TORRENT_TACKLE_DAMAGE 10
//タックル準備時間
#define TPRRENT_TACKLE_PREPARATION 60

//発射速度
#define TORRENT_SHOT_RATE 30

//ドロップ数
#define TORRENT_MIN_DROP 20
#define TORRENT_DROP 20

//葉っぱを飛ばしている時間
#define LEAF_CUTTER_TIME 1800

//次の葉っぱを飛ばす攻撃に移る時間
#define LEAF_CUTTER_INTERVAL 1800

//木の実を落としている時間
#define DROP_NUTS_TIME 1200

//次の木の実を落とす攻撃に移る時間
#define DROP_NUTS_INTERVAL 1200

//木の実の生成する時間
#define SPAWN_NUTS_INTERVAL 30

//木の実の生成地点数
#define SPAWN_NUTS_POINT 5

//木の実のスポーン地点
#define SPAWN_NUTS_Y 100

//スポーン地点の間隔
#define NUTS_SPAWN_SPACE 40

//-----------------------------------
//コンストラクタ
//-----------------------------------
Torrent::Torrent()
{
	left_move = true;
	attack = false;
	tackle_end = false;
	speed = -TORRENT_SPEED;
	tackle_end_point = 0;
	shot_rate = 0;
	leaf_cutter_interval = 0;
	drop_nuts_interval = 0;
	spawn_interval = 0;
	animation = 0;
	image_argument = 0;
	attack_time = 20;
	state = ENEMY_STATE::ATTACK;
	attack_state = TORRENT_ATTACK::NONE;

	/*当たり判定の設定*/
	area.width = 160;
	area.height = SCREEN_HEIGHT;
	location.x = SCREEN_WIDTH - area.width / 2;
	location.y = SCREEN_HEIGHT + SCREEN_HEIGHT / 2;

	type = new ENEMY_TYPE[1];
	type[0] = ENEMY_TYPE::SOIL;
	kind = ENEMY_KIND::TORRENT;

	//ドロップアイテムの設定
	drop_element = new ElementItem * [SOIL_DROP];
	drop_type_volume = SOIL_DROP;

	int volume = 0;

	for (int i = 0; i < SOIL_DROP; i++)
	{
		volume = TORRENT_MIN_DROP + GetRand(TORRENT_DROP);
		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}
}

//-----------------------------------
//デストラクタ
//-----------------------------------
Torrent::~Torrent()
{
	for (int i = 0; i < SOIL_DROP; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	delete[] type;
}

//-----------------------------------
//更新
//-----------------------------------
void Torrent::Update(const Player* player, const Stage* stage)
{
	Location old_location = location;	//前の座標

	switch (state)
	{
	case ENEMY_STATE::IDOL:
		Idol();
		break;
	case ENEMY_STATE::MOVE:
		Move(player->GetLocation());
		break;
	case ENEMY_STATE::FALL:
		Fall();
		break;
	case ENEMY_STATE::ATTACK:
		Attack(player->GetLocation());
		break;
	case ENEMY_STATE::DEATH:
		Death();
		break;
	default:
		break;
	}
}

//-----------------------------------
//アイドル状態
//-----------------------------------
void Torrent::Idol()
{
}

//-----------------------------------
//移動
//-----------------------------------
void Torrent::Move(const Location player_location)
{
}

//-----------------------------------
//落下
//-----------------------------------
void Torrent::Fall()
{
}

//-----------------------------------
//攻撃
//-----------------------------------
void  Torrent::Attack(Location player_location)
{

	if (0 < leaf_cutter_interval) //次の葉っぱを飛ばす攻撃までの時間のカウント
	{
		leaf_cutter_interval--;
	}

	if (0 < drop_nuts_interval) //次の木の実を落とす攻撃までの時間のカウント
	{
		drop_nuts_interval--;
	}

	switch (attack_state)
	{
	case TORRENT_ATTACK::TACKLE:
		Tackle();
		break;
	case TORRENT_ATTACK::LEAF_CUTTER:
		LeafCutter(player_location);
		break;
	case TORRENT_ATTACK::DROP_NUTS:
		DropNuts();
		break;
	case TORRENT_ATTACK::NONE:
		AttackNone();
		break;
	default:
		break;
	}
}

//-----------------------------------
//タックル攻撃
//-----------------------------------
void Torrent::Tackle()
{
	if (attack_time < 0)
	{
		location.x += speed;

		Location scroll; //画面スクロールを考慮した座標
		Location camera = CameraWork::GetCamera(); //カメラ
		scroll = location - camera;

		if (left_move)
		{
			if (scroll.x <= tackle_end_point)
			{
				tackle_end = true;
				left_move = !left_move;
			}
		}
		else
		{
			if (tackle_end_point <= scroll.x)
			{
				tackle_end = true;
				left_move = !left_move;
			}
		}
		
		if (tackle_end) //タックル終了
		{
			attack = false;
			TORRENT_ATTACK next_attack;	//次の攻撃
			if (leaf_cutter_interval < 0 && drop_nuts_interval < 0) //2つの攻撃が可能な時
			{
				next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) + 1);  //次の攻撃の設定

				switch (next_attack)
				{
				case TORRENT_ATTACK::LEAF_CUTTER:
					attack_state = TORRENT_ATTACK::LEAF_CUTTER;
					attack_time = LEAF_CUTTER_TIME;
					break;
				case TORRENT_ATTACK::DROP_NUTS:
					attack_state = TORRENT_ATTACK::DROP_NUTS;
					attack_time = DROP_NUTS_TIME;
					break;
				case TORRENT_ATTACK::TACKLE:
				case TORRENT_ATTACK::NONE:
				default:
					break;
				}
			}
			else if(leaf_cutter_interval < 0) //葉っぱを飛ばす攻撃だけが可能な時
			{
				attack_state = TORRENT_ATTACK::LEAF_CUTTER;
				attack_time = LEAF_CUTTER_TIME;
			}
			else if (drop_nuts_interval < 0) //木の実を飛ばす攻撃が可能な時
			{
				attack_state = TORRENT_ATTACK::DROP_NUTS;
				attack_time = DROP_NUTS_TIME;
			}
			else //どちらの攻撃も可能じゃないとき
			{
				if (leaf_cutter_interval < drop_nuts_interval)
				{
					attack_state = TORRENT_ATTACK::LEAF_CUTTER;
					attack_time = LEAF_CUTTER_TIME;
				}
				else
				{
					attack_state = TORRENT_ATTACK::DROP_NUTS;
					attack_time = DROP_NUTS_TIME;
				}
			}
		}
	}
	else
	{
		attack_time--;
	}
}

//-----------------------------------
//葉っぱを飛ばす攻撃
//-----------------------------------
void Torrent::LeafCutter(Location player_location)
{
	attack_time--;
	CreateLeaf(player_location);
	if (attack_time < 0) //攻撃の終了
	{
		leaf_cutter_interval = LEAF_CUTTER_INTERVAL; //次の攻撃までの時間の設定
		if (drop_nuts_interval < 0) //木の実を落とす攻撃が可能かどうか
		{
			TORRENT_ATTACK next_attack; //次の攻撃
			next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) * 2); //次の攻撃の設定

			switch (next_attack) //次の攻撃に移行
			{
			case TORRENT_ATTACK::TACKLE:
				attack_state = TORRENT_ATTACK::TACKLE;
				attack_time = TPRRENT_TACKLE_PREPARATION;
				tackle_end = false;
				if (left_move) //左に向いている
				{
					speed = -TORRENT_SPEED;
					tackle_end_point = 0 + area.width / 2;
				}
				else
				{
					speed = TORRENT_SPEED;
					tackle_end_point = SCREEN_WIDTH - area.width / 2;
				}
				break;
			case TORRENT_ATTACK::DROP_NUTS:
				attack_state = TORRENT_ATTACK::DROP_NUTS;
				attack_time = DROP_NUTS_TIME;
				break;
			case TORRENT_ATTACK::LEAF_CUTTER:
			case TORRENT_ATTACK::NONE:
			default:
				break;
			}
		}
		else
		{
			attack_state = TORRENT_ATTACK::TACKLE; //タックル攻撃に移行
			attack_time = TPRRENT_TACKLE_PREPARATION;
			tackle_end = false;
			if (left_move) //左に向いている
			{
				speed = -TORRENT_SPEED;
				tackle_end_point = 0 + area.width / 2;
			}
			else
			{
				speed = TORRENT_SPEED;
				tackle_end_point = SCREEN_WIDTH - area.width / 2;
			}
		}
	}
}

//-----------------------------------
//葉っぱの生成
//-----------------------------------
void Torrent::CreateLeaf(Location player_location)
{
	shot_rate++;

	if (shot_rate % TORRENT_SHOT_RATE == 0) //葉っぱの生成
	{
		Location spawn_location = location; //生成座標
		spawn_location.y = location.y - area.height / 2;
		BulletManager::GetInstance()->
			CreateEnemyBullet(new TorrentBullet(ENEMY_TYPE::WIND, spawn_location, player_location));
	}
}

//-----------------------------------
//木の実を落とす攻撃
//-----------------------------------
void Torrent::DropNuts()
{
	attack_time--;
	CreateNuts();
	if (attack_time < 0)
	{
		drop_nuts_interval = DROP_NUTS_INTERVAL;
		spawn_interval = 0;
		if (leaf_cutter_interval < 0) //木の実を落とす攻撃が可能かどうか
		{
			TORRENT_ATTACK next_attack; //次の攻撃
			next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) * 2); //次の攻撃の設定

			switch (next_attack) //次の攻撃に移行
			{
			case TORRENT_ATTACK::TACKLE:
				attack_state = TORRENT_ATTACK::TACKLE;
				attack_time = TPRRENT_TACKLE_PREPARATION;
				tackle_end = false;
				if (left_move) //左に向いている
				{
					speed = -TORRENT_SPEED;
					tackle_end_point = 0 + area.width / 2;
				}
				else
				{
					speed = TORRENT_SPEED;
					tackle_end_point = SCREEN_WIDTH - area.width / 2;
				}
				break;
			case TORRENT_ATTACK::LEAF_CUTTER:
				attack_state = TORRENT_ATTACK::LEAF_CUTTER;
				attack_time = LEAF_CUTTER_INTERVAL;
				break;
			case TORRENT_ATTACK::DROP_NUTS:
			case TORRENT_ATTACK::NONE:
			default:
				break;
			}
		}
		else
		{
			attack_state = TORRENT_ATTACK::TACKLE; //タックル攻撃に移行
			attack_time = TPRRENT_TACKLE_PREPARATION;
			tackle_end = false;
			if (left_move) //左に向いている
			{
				speed = -TORRENT_SPEED;
				tackle_end_point = 0 + area.width / 2;
			}
			else
			{
				speed = TORRENT_SPEED;
				tackle_end_point = SCREEN_WIDTH - area.width / 2;
			}
		}
	}
}

//-----------------------------------
//木の実の生成
//-----------------------------------
void Torrent::CreateNuts()
{
	bool spawn_point[SPAWN_NUTS_POINT]; //スポーン地点
	int spawn_volume = 0; //スポーン数
	bool spawn = false; //スポーンした

	spawn_interval++;
	
	if (spawn_interval % SPAWN_NUTS_INTERVAL == 0)
	{
		for (int i = 0; i < SPAWN_NUTS_POINT; i++)
		{
			spawn_point[i] = false;
		}

		spawn_volume = GetRand(SPAWN_NUTS_POINT - 1) + 1; //スポーン数の設定

		for (int i = 0; i < spawn_volume; i++) //木の実の生成
		{
			spawn = false;

			while (!spawn)
			{
				int spawn_point_rand; //スポーン地点
				spawn_point_rand = GetRand(SPAWN_NUTS_POINT - 1); //スポーン地点の設定
				if (!spawn_point[spawn_point_rand])
				{
					Location spawn_location; //スポーン地点
					spawn_location.x = ((spawn_point_rand + 1) * NUTS_SPAWN_SPACE);
					if (!left_move)
					{
						spawn_location.x += (area.width / 2);
					}
					spawn_location.y = SPAWN_NUTS_Y;
					spawn_point[spawn_point_rand] = true;
					spawn = true;

					BulletManager::GetInstance()->
						CreateEnemyNuts(new TorrentNuts(ENEMY_TYPE::WATER, spawn_location));
				}

			}
		}
	}
	

}

//-----------------------------------
// 攻撃していない
//-----------------------------------
void Torrent::AttackNone()
{
	attack_time--;
	if (attack_time < 0)
	{
		TORRENT_ATTACK next_attack;	//次の攻撃
		next_attack = static_cast <TORRENT_ATTACK>(GetRand(1) + 1);  //次の攻撃の設定
		
		next_attack = TORRENT_ATTACK::DROP_NUTS;
		switch (next_attack)
		{
		case TORRENT_ATTACK::LEAF_CUTTER:
			attack_state = TORRENT_ATTACK::LEAF_CUTTER;
			attack_time = LEAF_CUTTER_TIME;
			break;
		case TORRENT_ATTACK::DROP_NUTS:
			attack_state = TORRENT_ATTACK::DROP_NUTS;
			attack_time = DROP_NUTS_TIME;
			break;
		case TORRENT_ATTACK::TACKLE:
		case TORRENT_ATTACK::NONE:
		default:
			break;
		}
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource Torrent::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	if (attack_state == TORRENT_ATTACK::TACKLE)
	{
		if (!attack)
		{
			attack = true;
			ENEMY_TYPE attack_type[1] = { ENEMY_TYPE::SOIL };
			ret.damage = TORRENT_TACKLE_DAMAGE;
			ret.type = attack_type;
			ret.type_count = 1;
		}
	}
	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void Torrent::Death()
{
}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
void Torrent::HitBullet(const BulletBase* bullet)
{
}

//-----------------------------------
//描画
//-----------------------------------
void Torrent::Draw() const
{
	Location draw_location = location; //描画座標
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	DrawBox(draw_location.x - area.width / 2, draw_location.y - area.height / 2,
		draw_location.x + area.width / 2, draw_location.y + area.height / 2, 0xffffff, TRUE);
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location Torrent::GetLocation() const
{
	return location;
}