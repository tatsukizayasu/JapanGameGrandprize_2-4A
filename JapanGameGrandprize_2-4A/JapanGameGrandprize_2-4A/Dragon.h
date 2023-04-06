#pragma once
#include "EnemyBase.h"
#include"BoxCollider.h"
#include"DragonBullet.h"

enum class DRAGON_STATE
{
	NORMAL,   //通常移動 
	NONE //何も行動しない。
};

enum class DRAGON_ATTACK
{
	DITE = 0, //噛みつき
	TAIL_ATTACK, //尻尾の攻撃
	DREATH, //ブレス攻撃(火属性）
	ROAR, //咆哮した後に、雷を降らせる
	NONE //攻撃をしていない。
};

class Dragon :public EnemyBase
{
private:
	int animation; //画像のアニメーション
	int animation_time; //	画像切り替え間隔
	int magic_num; //遠距離攻撃を使った回数
	bool attack; //攻撃が当たったのか


	DRAGON_ATTACK attack_state; //攻撃状態

public:

	//コンストラクタ
	Dragon(Location);

	//デストラクタ
	~Dragon();

	//描画以外の更新を実行
	void Update(const class Player* player, const class Stage* stage)override;

	//描画
	void Draw()const override;

	//アイドル状態
	void Idol() override;

	//移動
	void Move(const Location player_location) override;

	//接近攻撃（噛みつき）時の動き
	void DiteMove(const Location player_location);

	//接近攻撃（尻尾攻撃）時の動き
	void TailMove(const Location player_location);

	//遠距離攻撃（ブレス）時の動き
	void DreathMove(const Location player_location);

	//遠距離攻撃（咆哮した後に雷を広範囲に降らせる）時の動き
	void RoarMove(const Location player_location);

	//落下
	void Fall() override;

	//攻撃
	void  Attack(const Location player_location) override;

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

