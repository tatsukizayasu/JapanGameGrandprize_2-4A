#pragma once
#include"EnemyBase.h"
#include"CameraWork.h"
#include"BoxCollider.h"

enum class DIRECTION
{
	LEFT = 0,
	RIGHT
};

enum class SLIME_ATTACK
{
	BEFORE_ATTACK,//UŒ‚‚·‚é‘O
	AFTER_ATTACK,//UŒ‚‚µ‚½Œã
};

class EnemySlime : public EnemyBase, public BoxCollider
{
private:

	int color;
	DIRECTION direction;
	SLIME_ATTACK slime_attack;

	int slime_image;
	int slime_angle;
	int wait_time;

	Location jump_distance;

	ElementItem drop_item;
public:

	EnemySlime();
	EnemySlime(float x, float y, float height, float width);
	~EnemySlime() {};

	//•`‰æˆÈŠO‚ÌXV‚ğÀs
	virtual void Update()override;
	//•`‰æ
	virtual void Draw()const override;

	//ƒAƒCƒhƒ‹ó‘Ô
	void Idol() override;

	//ˆÚ“®
	void Move(const Location player_location) override;

	//UŒ‚
	void  Attack(Location) override;

	//UŒ‚‚ª“–‚½‚Á‚Ä‚¢‚é‚©
	AttackResource HitCheck(const BoxCollider* collider) override;

	//€–S
	void Death() override;

	virtual bool HitBullet(const BulletBase* bullet)override;

	//À•W‚Ìæ“¾
	Location GetLocation() const override;
};
