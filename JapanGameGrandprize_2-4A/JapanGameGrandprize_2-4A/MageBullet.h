#pragma once
#include "EnemyBulletBase.h"

class MageBullet :
    public EnemyBulletBase
{
private:

    int image; //画像
    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
public:

    //コンストラクタ
    MageBullet(const ENEMY_TYPE , const Location , const Location);

    //デストラクタ
    ~MageBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override ;
};