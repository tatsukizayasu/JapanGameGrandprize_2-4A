//#pragma once
//
//#include"SlimeBossBody.h"
//#include"EnemyBase.h"
//
//#define BODY_MAX 30
//#define DATA 100
//
//class EnemySlimeBoss : public EnemyBase
//{
//private:
//
//	Location location_data[DATA];
//	ENEMY_STATE state;
//	SlimeBossBody* slime_boss_body[BODY_MAX];
//
//public:
//
//	EnemySlimeBoss();
//	~EnemySlimeBoss(){};
//
//	//描画以外の更新を実行
//	virtual void Update(const Stage* stage, const Player* player);
//	//描画
//	virtual void Draw()const;
//};

#pragma once

#define BODY_MAX 30
#define DATA 100

#include"EnemyBase.h"
#include"SlimeBossBody.h"

class EnemySlimeBoss : public EnemyBase
{
private:

	Location location_data[DATA];
	ENEMY_STATE state;
	SlimeBossBody* slime_boss_body[BODY_MAX];
	int slime_boss_jump_distance;
	int speed_y;

#ifdef _DEBUG
	ENEMY_STATE old_state; //一つ前の状態
	Location debug_location; //デバック用の座標
#endif // _DEBUG

public:

	EnemySlimeBoss(Location spawn_location);
	~EnemySlimeBoss();

	//描画以外の更新を実行
	virtual void Update(const Player* player, const Stage* stage)override;
	//描画
	virtual void Draw()const override;

	//移動
	void Move(const Location player_location) override;

	//落下
	void Fall() override;

	void Idol() override;

	//攻撃
	void  Attack(Location) override;

	//攻撃が当たっているか
	AttackResource Hit() override;

	//死亡
	void Death() override;

	virtual void HitBullet(const BulletBase* bullet)override;

	//座標の取得
	Location GetLocation() const override;

#ifdef _DEBUG
	//更新(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//描画(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};