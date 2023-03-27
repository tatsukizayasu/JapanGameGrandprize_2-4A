//#pragma once
//#include"EnemyBase.h"
//#include"CameraWork.h"
//
//enum class BODY_TYPE
//{
//	head,
//	body
//};
//
//class SlimeBossBody: public EnemyBase
//{
//private:
//
//	bool attack; //UŒ‚‚ª“–‚½‚Á‚½‚©
//
//	int slimeboss_image;
//	BODY_TYPE body_type;
//public:
//
//	SlimeBossBody(int x, int y, int speed, int hp, int slime_min_drop, int slime_drop, BODY_TYPE body_type);
//	~SlimeBossBody();
//
//	//•`‰æˆÈŠO‚ÌXV‚ğÀs
//	virtual void Update(const class Player* player, const class Stage* stage)override;
//	//•`‰æ
//	virtual void Draw()const override;
//
//	//ˆÚ“®
//	void Move(const Location player_location) override;
//
//	//—‰º
//	void Fall() override;
//	
//	void Idol() override;
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
//
//	void SetLocation(Location location);
//
//	BODY_TYPE GetBodyType() const { return body_type; }
//};