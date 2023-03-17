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
	int standby_time; //硬直時間
	int magic_num; //魔法攻撃した数
	int harpy_image; //ハーピィの画像。
	float travel; //X座標に動く量
	float travel_y; //ｙ座標に動く量
	bool magic_attack; //魔法攻撃
	bool attack; //攻撃が当たったか
	bool physical_attack; //物理攻撃に入る（true)なら
	bool inversion; //反転（壁にあったった)
	HARPY_STATE action_type; //行動パターン
	HARPY_ATTACK attack_state; //攻撃状態

public:

	//コンスタラクタ
	Harpy();

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

	//落下
	void Fall() override;

	//攻撃
	void  Attack(Location) override;

	//攻撃が当たっているか
	AttackResource Hit() override;

	//死亡
	void Death() override;

	//プレイヤーの弾丸との当たり判定
	void HitBullet(const BulletBase* bullet) override;

	//座標の取得
	Location GetLocation() const override;

};