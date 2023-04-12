#pragma once
#include "EfectExplosion.h"
#include "SphereCollider.h"
#include "define.h"
#include "Stage/Stage.h"
#include "Stage/MapChip.h"

#define BULLET_SPEED 20
#define EXPLOSION_BULLET_SPEED 10
#define MELT_BULLET_SPEED 15
#define PARARYSIS_BULLET_SPEED 10
#define POISON_BULLET_SPEED 18

#define ORANGE 0xff8f00
#define PURPLE 0x00ff00
#define BLUE 0x0000ff
#define GLAY 0xbebebe

enum class PLAYER_STATE;

class BulletBase : public SphereCollider
{
protected:

	Area area;           //範囲
	float damage;        //弾のダメージ
	float damage_second; //秒間ダメージ
	int debuff_time;	 //弾の効果時間
	int efect_count;	 //エフェクトの時間
	float scrool_x;      //弾のスクロールの値(X)
	float scrool_y;		 //弾のスクロールの値(Y)
	bool delete_flg;     //弾の削除フラグ
	bool efect_end;		 //エフェクトの終わりフラグ
	bool player_direction;//プレイヤーの向き
	ChemicalFormulaParameter* chemical_formula;//化合物

	PLAYER_STATE player_state;
	ATTRIBUTE attribute;
	EfectExplosion* efect_explosion;
public:

	BulletBase();
	BulletBase(float,float);
	~BulletBase() {};

	virtual void Draw() const = 0;
	virtual void Update(const Stage*) = 0;


	bool HitBlock(const Stage*);
	bool GetEfectFlg() const;
	int GetDebuffTime() const;
	int GetDamage() const;
	ATTRIBUTE GetAttribute() const;
};