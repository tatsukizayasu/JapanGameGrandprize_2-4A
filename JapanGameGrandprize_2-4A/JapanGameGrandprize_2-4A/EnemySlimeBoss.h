#pragma once

#include"EnemyBase.h"
#include"CameraWork.h"

#include"SlimeBossBullet.h"
#include"SlimeBossThunder.h"


enum class ATTACKTYPE
{
	NONE,
	MAGIC_BULLET,
	THUNDER
};

class EnemySlimeBoss : public EnemyBase
{
private:

	int slime_boss_image;
	int slime_boss_jump_distance;
	int speed_y;
	int wait_time;
	int cloud_move_time;
	int cloud_brightness;
	int magic_circle_image;

	void DrawHPBar(const int) const;//hpバー表示

	ENEMY_STATE now_state;
	Location cloud_location;

	ATTACKTYPE attack_type;

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
	void Update_Cloud(const Player* player);

	void Draw_Cloud()const;

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
	void Thunder(const Location player_location);


#ifdef _DEBUG
	//更新(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//描画(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG
};