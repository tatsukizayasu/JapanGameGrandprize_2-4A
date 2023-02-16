#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"

enum DIRECTION
{
	left = -1,
	right = 1
};

enum class SLIME_STATE
{
	IDOL,   //アイドル状態
	MOVE,   //移動
	ATTACK, //攻撃
	BOUNCE, //壁、敵に跳ね返る
	DEATH,  //死亡
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:
	int color;
	int direction;

	int slime_image;

	Location jump_distance;

	ElementItem drop_item;

	SLIME_STATE state;

public:
	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//描画以外の更新を実行
	virtual void Update()override;
	//描画
	virtual void Draw()const override;

	void HitPlayer(BoxCollider* boxcollider);
	void HitStage();
	void AttackJudgement(BoxCollider* boxcollider);
	void Attack();

	virtual void HitBullet(Bullet* bullet)override {};
};
