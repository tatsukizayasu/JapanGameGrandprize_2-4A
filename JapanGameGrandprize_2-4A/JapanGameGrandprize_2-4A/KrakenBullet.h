#pragma once
#include "EnemyBulletBase.h"
class KrakenBullet :
    public EnemyBulletBase
{
    int image; //画像

    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
public:

    //コンスタラクタ
    KrakenBullet(Location, Location);

    //デストラクタ
    ~KrakenBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};

