#include "Torrent.h"
#include "DxLib.h"
#include "Player.h"
#include "Stage/Stage.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
Torrent::Torrent()
{
}

//-----------------------------------
//デストラクタ
//-----------------------------------
Torrent::~Torrent()
{
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
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource Torrent::Hit()
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

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
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location Torrent::GetLocation() const
{
	return location;
}