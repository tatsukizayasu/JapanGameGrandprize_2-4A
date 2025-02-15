#pragma once
#include"EnemyBulletBase.h"

class SlimeBossBullet :
    public EnemyBulletBase
{
    int image[12]; //画像
    int image_type;
    int image_change_time;
    int image_change_no;
    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
    int gravity_power;


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