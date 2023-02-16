#pragma once
#include"EnemyBase.h"
#include"BoxCollider.h"
#include"Player.h"
#include"Stage/Stage.h"

enum class GHOST_STATE
{
	NORMAL,   //通常移動
	LEFT_lOWER,   //左下に移動
	LEFT_UPPER,   //左上に移動
	RIGHT_LOWER,  //右下に移動
	RIGHT_UPPER,  //右上に移動
	PHYSICAL_ATTACK,       //物理攻撃
	MAGIC_ATTACK, //魔法攻撃
	DEATH,   //死亡
};


class EnemyGhost : public EnemyBase, public BoxCollider
{
private:

	int standby_time; //硬直時間
	int ghost_hp; //ゴーストのHP
	float bullet_x; //弾丸
	float bullet_y; //弾丸
	float bullet_speed_x; //弾丸スピード
	float bullet_speed_y; //弾丸スピード
	float player_x; //プレイヤーの座標を保存
	float player_y; //プレイヤーの座標を保存
	bool magic_attack; //魔法攻撃
	bool ghost_vanish; //ゴーストが透明化したらtrue
	bool physical_attack; //物理攻撃に入る（true)なら
	bool setting; //弾丸初期処理
	GHOST_STATE action_type; //行動パターン

public:

	EnemyGhost(); //コンスタラクタ

	//描画以外の更新を実行
	void Update()override;

	//描画
	void Draw()const override;

	//ゴーストのアタック処理
	void GhostAttack();

	//ゴーストの動きを決める
	void GhostMove(Player* player);

	//プレイヤーの弾丸との当たり判定
	void HitBullet(Bullet* bullet);


};
