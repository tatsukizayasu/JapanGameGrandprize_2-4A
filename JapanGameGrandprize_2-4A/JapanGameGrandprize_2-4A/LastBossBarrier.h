#pragma once
#include "SphereCollider.h"

//バリアの量
#define BARRIER_VOLUME 5

class LastBossBarrier :
    public SphereCollider
{
private:
    bool end_deployment; //バリアの展開終了
    int* images; //画像
    int count; //カウント
    int animation[BARRIER_VOLUME]; //アニメーション
    double size; //大きさ
    double angle; //角度
    int durability; //耐久値
    int old_durability; //前回の耐久値
    int volume; //割れたバリアの量

private:

    //バリアの展開
    void Deployment();
public:
    //コンストラクタ
    LastBossBarrier(const Location);

    //デストラクタ
    ~LastBossBarrier();

    //更新
    void Update();

    //プレイヤーの弾との当たり判定
    void HitBullet(const class BulletBase* bullet);

    //描画
    void Draw() const;

    //耐久値バーの描画
    void DrawDurabilityBar() const;

    //破壊された
    bool Break() const;
};

