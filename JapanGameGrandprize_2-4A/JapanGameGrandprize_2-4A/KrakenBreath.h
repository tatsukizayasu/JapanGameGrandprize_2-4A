#pragma once
#include "EnemyBulletBase.h"
class KrakenBreath :
    public EnemyBulletBase
{
    int image; //画像

    float x_speed; //Xのスピード
    float y_speed; //Yのスピード


public:

    //コンスタラクタ
    KrakenBreath(Location, Location);

    //デストラクタ
    ~KrakenBreath();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};

