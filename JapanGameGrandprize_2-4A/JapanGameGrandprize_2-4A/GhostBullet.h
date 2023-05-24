#pragma once
#include "EnemyBulletBase.h"

class GhostBullet :
    public EnemyBulletBase
{
private:

    int image; //画像

    int x_speed; //Xのスピード
    int y_speed; //Yのスピード

    //エフェクト
    int tick;
    int frame;
    float angle;
public:

    //コンストラクタ
    GhostBullet(const Location, const Location);

    //デストラクタ
    ~GhostBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};