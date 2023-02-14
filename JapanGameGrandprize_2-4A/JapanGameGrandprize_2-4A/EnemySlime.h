#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"


struct ATTACK_START
{
	float x;	//c
	float y;	//‰¡
};

enum DIRECTION
{
	left = -1,
	right = 1
};

enum class SLIME_STATE
{
	IDOL,   //ƒAƒCƒhƒ‹ó‘Ô
	MOVE,   //ˆÚ“®
	ATTACK, //UŒ‚
	DEATH,  //€–S
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:
	int color;
	int a;
	int direction;
	int jump_angle;

	ATTACK_START attack_start;
	SLIME_STATE state;

public:
	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//•`‰æˆÈŠO‚ÌXV‚ğÀs
	virtual void Update()override;
	//•`‰æ
	virtual void Draw()const override;

	void Hit();
	void HitStage();
	void AttackJudgement(BoxCollider* boxcollider);
	void Attack();
};
