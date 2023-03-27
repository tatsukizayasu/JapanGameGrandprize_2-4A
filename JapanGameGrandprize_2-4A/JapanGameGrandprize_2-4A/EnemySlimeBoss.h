//#pragma once
//
//#include"EnemyBase.h"
//#include"CameraWork.h"
//#include"BoxCollider.h"
//
//enum class SLIME_ATTACK
//{
//	BEFORE_ATTACK,//UŒ‚‚·‚é‘O
//	AFTER_ATTACK,//UŒ‚‚µ‚½Œã
//};
//
//class EnemySlimeBoss : public EnemyBase
//{
//private:
//
//	bool attack; //UŒ‚‚ª“–‚½‚Á‚½‚©
//
//	int color;
//	SLIME_ATTACK slime_attack;
//
//	int slimeboss_image;	
//
//	Location jump_distance;
//
//	ElementItem drop_item;
//public:
//
//	EnemySlimeBoss();
//	~EnemySlimeBoss() {};
//
//	//•`‰æˆÈŠO‚ÌXV‚ğÀs
//	virtual void Update(const class Player* player, const class Stage* stage)override;
//	//•`‰æ
//	virtual void Draw()const override;
//
//	//ƒAƒCƒhƒ‹ó‘Ô
//	void Idol() override;
//
//	//ˆÚ“®
//	void Move(const Location player_location) override;
//
//	//—‰º
//	void Fall() override;
//
//	//UŒ‚
//	void  Attack(Location) override;
//
//	//UŒ‚‚ª“–‚½‚Á‚Ä‚¢‚é‚©
//	AttackResource Hit() override;
//
//	//€–S
//	void Death() override;
//
//	virtual void HitBullet(const BulletBase* bullet)override;
//
//	//À•W‚Ìæ“¾
//	Location GetLocation() const override;
//};