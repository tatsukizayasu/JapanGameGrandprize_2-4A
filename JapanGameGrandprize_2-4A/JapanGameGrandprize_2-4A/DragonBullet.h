#pragma once
#include"EnemyBulletBase.h"

#define DRAGON_BULLET_IMAGES_NUM (10)
#define DRAGON_BULLET_IMAGE_SIZE (192)
#define DRAGON_BULLET_IMAGE_CENTER (96)

class DragonBullet :
    public EnemyBulletBase
{

    float direction; //進行方向
    int x_speed; //Xのスピード
    int y_speed; //Yのスピード

    static int images[DRAGON_BULLET_IMAGES_NUM]; //画像
    int frame_count;
    int images_index;

    static const float distance[DRAGON_BULLET_IMAGES_NUM];
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

