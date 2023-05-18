#pragma once
#include "Define.h"

//エフェクト
struct Effect
{
	bool draw; //描画する
	Location location; //座標
	int* images; //画像
	int animation; //アニメション
	double size; //大きさ
	double angle; //角度
	int alpfa_brend; //透明度
};

enum class SPECIAL_MOVES_STATE
{
	CHARGE = 0,	//チャージ
	FALL,		//落下
	LANDING,	//着弾
};

class LastBossSpecialMoves
{
private:
	bool end; //終了
	int tick; //更新
	Effect* effect; //エフェクト
	Effect* charge_effect; //チャージエフェクト
	SPECIAL_MOVES_STATE state; //状態
public:
	//コンストラクタ
	LastBossSpecialMoves(const Location);

	//デストラクタ
	~LastBossSpecialMoves();

	//更新
	void Update();

	//描画
	void Draw() const;

	//ダメージの取得
	int GetDamage() const;

	//終了情報の取得
	bool GetEnd() const;

	//チャージ終了
	bool EndCharge() const;
};

