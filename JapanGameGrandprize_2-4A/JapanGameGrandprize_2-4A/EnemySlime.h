#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"
#include"BoxCollider.h"

enum class DIRECTION
{
	LEFT = 0,
	RIGHT
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:
	int color;
	DIRECTION direction;

	int slime_image;
	int slime_angle;

	Location jump_distance;

	ElementItem drop_item;

public:
	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//描画以外の更新を実行
	virtual void Update()override;
	//描画
	virtual void Draw()const override;

	//アイドル状態
	void Idol() override;

	//移動
	void Move(const Location player_location) override;

	//攻撃
	AttackResource Attack(const BoxCollider* collider) override;

	//死亡
	void Death() override;

	void HitStage();

	void KnockBack();

	virtual bool HitBullet(const BulletBase* bullet)override {
		bool ret = false; //戻り値

		return ret;
	};

	//座標の取得
	Location GetLocation() const override;
};
