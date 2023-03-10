#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Stage/Stage.h"
#include"GhostBullet.h"

enum class GHOST_STATE
{
	NORMAL,   //通常移動 左に移動
	NORMAL_RIGHT, //通常移動 右に移動
	LEFT_lOWER,   //左下に移動
	LEFT_UPPER,   //左上に移動
	RIGHT_LOWER,  //右下に移動
	RIGHT_UPPER,  //右上に移動
};

enum class GHOST_ATTACK
{
	PHYSICAL_ATTACK = 0, //物理攻撃
	MAGIC_ATTACK, //魔法攻撃
	NONE
};

class EnemyGhost :public EnemyBase
{
private:
	int standby_attack; //次の攻撃待機時間
	int standby_time; //硬直時間
	int ghost_image; //ゴーストの画像。
	float speed; //ゴーストの移動速度
	bool magic_attack; //魔法攻撃
	bool attack; //攻撃が当たったか
	bool physical_attack; //物理攻撃に入る（true)なら
	GHOST_STATE action_type; //行動パターン
	GHOST_ATTACK attack_state; //攻撃状態
private:

	//ゴーストの動きを決める
	void GhostMove(const Location player_location);
public:

	//コンスタラクタ
	EnemyGhost(); 

	//デストラクタ
	~EnemyGhost();

	//描画以外の更新を実行
	void Update(const class Player* player, const class Stage* stage)override;

	//描画
	void Draw()const override;

	//アイドル状態
	void Idol() override;

	//移動
	void Move(const Location player_location) override;

	//落下
	void Fall() override;

	//攻撃
	void  Attack(Location) override;

	//攻撃が当たっているか
	AttackResource Hit() override;

	//死亡
	void Death() override;

	//プレイヤーの弾丸との当たり判定
	void HitBullet(const BulletBase* bullet) override;

	//座標の取得
	Location GetLocation() const override;

};
