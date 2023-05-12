#pragma once
#include "EnemyBulletBase.h"

class LastBossMagic :
    public EnemyBulletBase
{
private:

	bool standby; //スタンバイ
	bool can_delete; //削除可能
	int* images; //画像
	double size; //大きさ
	int standby_time; //準備時間

	int animation; //アニメーション

	int argument; //画像の引数
public:
	//コンストラクタ
	LastBossMagic();

	//コンストラクタ
	LastBossMagic(const Location);

	//デストラクタ
	~LastBossMagic();

	//更新
	void Update() override;

	//描画
	void Draw() const override;

	//削除可能フラグの取得
	bool GetCanDelete() const;

	//スタンバイ状態の取得
	bool GetDoStandby() const;
};

