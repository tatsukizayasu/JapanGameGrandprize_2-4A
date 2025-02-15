#pragma once
#include "EnemyBase.h"
#include"BoxCollider.h"
#include"HarpyBullet.h"

enum class HARPY_STATE
{
	NORMAL,   //通常移動 左に移動
	NORMAL_RIGHT, //通常移動 右に移動
	NONE //何も行動しない。
};

enum class HARPY_ATTACK
{
	PHYSICAL_ATTACK = 0, //物理攻撃
	MAGIC_ATTACK, //魔法攻撃
	NONE //攻撃をしていない。
};

class Harpy :public EnemyBase
{
private:

	int standby_attack; //次の攻撃待機時間
	int time; //時間測定
	int standby_time; //硬直時間
	int magic_num; //魔法攻撃した数
	int magic_time; //魔法攻撃の間隔。標
	int standby_num;
	int animation; 
	int animation_time; 
	float vector; //ベクトル
	float speed;
	int physical_time; //物理攻撃時間
	float range; //プレイヤーとの距離	
	float range_y; //プレイヤーとの距離Y座
	float travel; //X座標に動く量
	float travel_y; //ｙ座標に動く量
	float old_x; //復帰する座標
	float old_y; //復帰する座標
	bool magic_attack; //魔法攻撃
	bool attack; //攻撃が当たったか
	bool physical_attack; //物理攻撃に入る（true)なら
	bool go_back; //落下する前の座標に戻る。

	HARPY_STATE action_type; //行動パターン
	HARPY_ATTACK attack_state; //攻撃状態
	Area size;          //画像サイズ
public:

	//コンスタラクタ
	Harpy(Location);

	//デストラクタ
	~Harpy();

	//描画以外の更新を実行
	void Update(const class Player* player, const class Stage* stage)override;

	//描画
	void Draw()const override;

	//アイドル状態
	void Idol() override;

	//移動
	void Move(const Location player_location) override;

	//元の座標に戻る
	void Comeback();

	//接近攻撃（物理攻撃）時の動き
	void PhysicalMove(const Location player_location);

	//落下
	void Fall() override;

	//攻撃
	void  Attack(const Location) override;

	//攻撃が当たっているか
	AttackResource Hit() override;

	//死亡
	void Death() override;

	//プレイヤーの弾丸との当たり判定
	void HitBullet(const BulletBase* bullet) override;

	//座標の取得
	Location GetLocation() const override;

#ifdef _DEBUG
	//更新(DotByDot)
	void Update(const ENEMY_STATE state) override;

	//描画(DotByDot)
	void DebugDraw() override;
#endif //_DEBUG

};