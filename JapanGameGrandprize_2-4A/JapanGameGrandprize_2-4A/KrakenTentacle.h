#pragma once
#include"EnemyBase.h"

enum class KRAKEN_TENTACLE
{
	NONE = 0,  //攻撃をしていない。
	TENTACLE_ATTACK, //触手攻撃
};

class KrakenTentacle :public EnemyBase
{
private:

	int image;
	int time; //攻撃開始を測る


	float old_x;
	bool go_back; //古い座標に戻る
	bool attack_state; //攻撃開始
	bool attack;

	KRAKEN_TENTACLE attack_move;

public:
	//コンストラクタ
	KrakenTentacle(Location);

	//デストラクタ
	~KrakenTentacle();

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
	void  Attack(const Location) override;

	//攻撃が当たっているか
	AttackResource Hit() override;

	//死亡
	void Death() override;

	//プレイヤーの弾丸との当たり判定
	void HitBullet(const BulletBase* bullet) override;

	//座標の取得
	Location GetLocation() const override;

#ifdef _DEBUG
	//更新(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//描画(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};

