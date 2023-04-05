#pragma once
#include"EnemyBulletBase.h"

class DragonBullet :
    public EnemyBulletBase
{
    int image; //画像

    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
public:

    //コンスタラクタ
    DragonBullet(Location, Location);

    //デストラクタ
    ~DragonBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};

