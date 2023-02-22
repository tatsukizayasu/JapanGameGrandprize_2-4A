#pragma once
#include "EnemyBulletBase.h"
#include "SphereCollider.h"

class MageBullet :
    public EnemyBulletBase, public SphereCollider
{
private:
    int image; //画像
    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
public:
    //コンストラクタ
    MageBullet(ENEMY_TYPE ,Location , Location);

    //デストラクタ
    ~MageBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override ;
};

