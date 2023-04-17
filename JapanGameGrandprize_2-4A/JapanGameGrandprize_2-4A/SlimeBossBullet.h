#pragma once
#include"EnemyBulletBase.h"

class SlimeBossBullet :
    public EnemyBulletBase
{
    int image; //画像

    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
public:

    //コンスタラクタ
    SlimeBossBullet(Location, Location);

    //デストラクタ
    ~SlimeBossBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};