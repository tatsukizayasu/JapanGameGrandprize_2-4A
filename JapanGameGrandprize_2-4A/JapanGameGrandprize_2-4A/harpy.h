//#pragma once
//#include "EnemyBase.h"
//#include"BoxCollider.h"
//
//enum class HARPY_STATE
//{
//	NORMAL,   //通常移動 左に移動
//	NORMAL_RIGHT, //通常移動 右に移動
//	LEFT_lOWER,   //左下に移動
//	LEFT_UPPER,   //左上に移動
//	RIGHT_LOWER,  //右下に移動
//	RIGHT_UPPER,  //右上に移動
//};
//
//enum class HARPY_ATTACK
//{
//	PHYSICAL_ATTACK = 0, //物理攻撃
//	MAGIC_ATTACK, //魔法攻撃
//	NONE //攻撃をしていない。
//};
//
//class Harpy :public EnemyBase,public BoxCollider
//{
//private:
//	int harpy_images; //ハーピィの画像
//	bool magic_attack; //魔法攻撃
//	bool physical_attack; //物理攻撃に入る（true)なら
//	HARPY_STATE action; //行動
//	HARPY_ATTACK attack; //攻撃
//public:
//
//	//コンストラクタ
//	Harpy(); 
//
//	//デストラクタ
//	~Harpy();
//
//	//描画以外の更新を実行
//	void Update()override;
//
//	//描画
//	void Draw()const override;
//
//	//ハーピィの動き
//	void Move(const Location player_location) override;
//	
//	//プレイヤーの距離を取得後ハーピィの動きを決める。
//	void Distance(const Location player_location);
//
//	////アイドル状態
//	//void Idol() override;
//
//	////攻撃
//	//void  Attack(Location) override;
//
//	////攻撃が当たっているか
//	//AttackResource HitCheck(const BoxCollider* collider) override;
//
//	////死亡
//	//void Death() override;
//	//
//	////プレイヤーの弾丸との当たり判定
//	//bool HitBullet(const BulletBase* bullet) override;
//
//	////座標の取得
//	//Location GetLocation() const override;
//	
//};