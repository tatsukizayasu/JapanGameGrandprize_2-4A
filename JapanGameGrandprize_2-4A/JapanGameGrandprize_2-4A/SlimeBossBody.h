#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"


class SlimeBossBody: public EnemyBase
{
private:

	bool attack; //攻撃が当たったか
	STAGE_DIRECTION hit_direction_all;

#ifdef _DEBUG
	ENEMY_STATE old_state; //一つ前の状態
	Location debug_location; //デバック用の座標
#endif // _DEBUG

public:

	SlimeBossBody(int x, int y);
	~SlimeBossBody();

	//描画以外の更新を実行
	virtual void Update(const class Player* player, const class Stage* stage)override;
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

	void SetLocation(Location location);

	void WalkWall();

#ifdef _DEBUG
	//更新(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//描画(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};












