//#pragma once
//#include"EnemyBase.h"
//#include"CameraWork.h"
//
//enum class BODY_TYPE
//{
//	HEAD,
//	BODY
//};
//
////ボスの動き
//enum class MOVE_STATE
//{
//	MOVE_SIDE, //横に移動
//	WALK_WALL, //壁を這う
//};
//
//class SlimeBossBody: public EnemyBase
//{
//private:
//
//	bool attack; //攻撃が当たったか
//	int slimeboss_image;
//	BODY_TYPE body_type;
//	MOVE_STATE move_state;
//	int speed_y;
//
//#ifdef _DEBUG
//	ENEMY_STATE old_state; //一つ前の状態
//	Location debug_location; //デバック用の座標
//#endif // _DEBUG
//
//public:
//
//	SlimeBossBody(int x, int y, int hp, int slime_min_drop, int slime_drop, BODY_TYPE body_type);
//	~SlimeBossBody();
//
//	//描画以外の更新を実行
//	virtual void Update(const class Player* player, const class Stage* stage)override;
//	//描画
//	virtual void Draw()const override;
//
//	//移動
//	void Move(const Location player_location) override;
//
//	//落下
//	void Fall() override;
//	
//	void Idol() override;
//
//	//攻撃
//	void  Attack(Location) override;
//
//	//攻撃が当たっているか
//	AttackResource Hit() override;
//
//	//死亡
//	void Death() override;
//
//	virtual void HitBullet(const BulletBase* bullet)override;
//
//	//座標の取得
//	Location GetLocation() const override;
//
//	void SetLocation(Location location);
//
//	BODY_TYPE GetBodyType() const { return body_type; }
//
//	void WalkWall();
//
//#ifdef _DEBUG
//	//更新(DotByDot)
//	void Update(const ENEMY_STATE state) override;
//
//	//描画(DotByDot)
//	void DebugDraw() override;
//#endif //_DEBUG
//};