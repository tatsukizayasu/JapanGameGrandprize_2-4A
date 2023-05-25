#pragma once
#include "EnemyBulletBase.h"

class LastBossMagic :
    public EnemyBulletBase
{
private:

	bool standby; //スタンバイ
	bool can_delete; //削除可能
	int* images; //画像
	int image_num; //画像の枚数
	double size; //大きさ
	double image_size; //画像の大きさ
	int angle; //角度
	int standby_time; //準備時間
	int magic_circle_image; //魔法陣の画像
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

