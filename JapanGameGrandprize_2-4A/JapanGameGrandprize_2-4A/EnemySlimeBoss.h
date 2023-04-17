#pragma once

#include"EnemyBase.h"
#include"CameraWork.h"
#include"SlimeBossBullet.h"

enum class MOVE_STATE
{
	MOVE,
	WALL_MOVE
};

class EnemySlimeBoss : public EnemyBase
{
private:

	ENEMY_STATE state;
	MOVE_STATE move_state;
	int slime_boss_jump_distance;
	int speed_y;
	int wait_time;
	int breath_time;

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

	void MagicBullet(const Location player_location);

#ifdef _DEBUG
	//更新(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//描画(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};