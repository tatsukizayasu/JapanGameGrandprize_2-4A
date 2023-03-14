#pragma once
#include "EnumEnemyType.h"
#include "SphereCollider.h"

class EnemyBulletBase :
	public SphereCollider
{
public:

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() const = 0;

	//画面外に出たかどうか
	bool ScreenOut();

	//ステージとの当たり判定
	bool HitStage(const class Stage* stage) const;

	//プレイヤーの弾との当たり判定
	bool HitPlayerBullet(const class BulletBase* player_bullet) const;

	//ダメージの取得
	int GetDamage() const;

	//タイプの取得
	ENEMY_TYPE GetType() const;
protected:

	int damage; //ダメージ
	int speed; //速度

	ENEMY_TYPE type; //属性	
};