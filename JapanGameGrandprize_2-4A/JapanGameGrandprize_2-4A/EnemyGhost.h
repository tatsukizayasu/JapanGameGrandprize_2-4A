#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Player.h"

class EnemyGhost : public EnemyBase, public BoxCollider
{
private:

	int action_time; //行動時間
	int action_type; //行動パターン
	bool ghost_death; //ゴーストが倒されたらtrue
	bool ghost_vanish; //ゴーストが透明化したらtrue

public:

	EnemyGhost(); //コンスタラクタ

	//描画以外の更新を実行
	void Update()override;

	//描画
	void Draw()const override;

	void GhostAttack(); //ゴーストのアタック処理

	void GhostMove(Player* player);

	bool GhostRange();
};
