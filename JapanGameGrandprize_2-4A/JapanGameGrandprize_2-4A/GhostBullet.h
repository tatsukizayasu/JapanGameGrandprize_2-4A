#pragma once
#include "EnemyBulletBase.h"
class GhostBullet :
    public EnemyBulletBase
{
private:

    int image; //画像

    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
public:

    //コンストラクタ
    GhostBullet(Location, Location);

    //デストラクタ
    ~GhostBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};

