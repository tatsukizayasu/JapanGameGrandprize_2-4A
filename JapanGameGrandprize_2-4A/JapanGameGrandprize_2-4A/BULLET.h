#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
#include "define.h"

enum class PLAYER_STATE;
class BulletBase : public SphereCollider
{
protected:
	float damage;          //弾のダメージ
	int debuff_time;	 //弾の効果時間
	int efect_count;	 //エフェクトの時間
	float scrool_x;      //弾のスクロールの値
	bool delete_flg;     //弾の削除フラグ
	bool efect_end;		 //エフェクトの終わりフラグ
	bool player_direction;//プレイヤーの向き

	PLAYER_STATE player_state;
	ATTRIBUTE attribute;
	EfectExplosion* efect_explosion;
public:
	BulletBase();
	BulletBase(float,float);
	~BulletBase() {};

	virtual void Draw() const = 0;
	virtual void Update() = 0;

	bool GetEfectFlg() const;
	float GetDebuffTime() const;
	float GetDamage() const;
	ATTRIBUTE GetAttribute() const;

};