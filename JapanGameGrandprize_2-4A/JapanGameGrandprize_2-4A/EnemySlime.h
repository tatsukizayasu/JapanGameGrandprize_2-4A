#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"
#include"BoxCollider.h"

enum class SLIME_ATTACK
{
	BEFORE_ATTACK,//UŒ‚‚·‚é‘O
	AFTER_ATTACK,//UŒ‚‚µ‚½Œã
};

class EnemySlime :
	public EnemyBase
{
private:
	bool attack; //UŒ‚‚ª“–‚½‚Á‚½‚©

	SLIME_ATTACK slime_attack;

	int image_type;
	int image_change_time;
	int image_addition;
	int slime_angle;
	int wait_time;

	Location jump_distance;

public:

	EnemySlime(Location);
	~EnemySlime();

	//•`‰æˆÈŠO‚ÌXV‚ğÀs
	virtual void Update(const class Player* player, const class Stage* stage)override;
	//•`‰æ
	virtual void Draw()const override;

	//ƒAƒCƒhƒ‹ó‘Ô
	void Idol() override;

	//ˆÚ“®
	void Move(const Location player_location) override;

	//—‰º
	void Fall() override;

	//UŒ‚
	void  Attack(Location) override;

	//UŒ‚‚ª“–‚½‚Á‚Ä‚¢‚é‚©
	AttackResource Hit() override;

	//€–S
	void Death() override;

	virtual void HitBullet(const BulletBase* bullet)override;

	//À•W‚Ìæ“¾
	Location GetLocation() const override;
};