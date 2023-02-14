#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Player.h"

enum class GHOST_STATE
{
	NORMAL,   //通常移動
	LEFT_lOWER,   //左下に移動
	LEFT_UPPER,   //左上に移動
	RIGHT_LOWER,  //右下に移動
	RIGHT_UPPER,  //右上に移動
	ATTACK,   //攻撃
	DEATH,   //死亡
};


class EnemyGhost : public EnemyBase, public BoxCollider
{
private:

	int action_time; //行動時間
	bool ghost_vanish; //ゴーストが透明化したらtrue
	GHOST_STATE action_type; //行動パターン
public:

	EnemyGhost(); //コンスタラクタ

	//描画以外の更新を実行
	void Update()override;

	//描画
	void Draw()const override;

	void GhostAttack(); //ゴーストのアタック処理

	void GhostMove(Player* player);

	void HitBullet(Bullet* bullet);

	bool GhostRange();
};
