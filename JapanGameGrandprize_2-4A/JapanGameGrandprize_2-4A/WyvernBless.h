#pragma once
#include "EnemyBulletBase.h"
#define WYVERN_BLESS_EXTEND_RATE (0.2f)
#define WYVERN_IMAGES_NUM (9)
class WyvernBless :
    public EnemyBulletBase
{
private:
    //移動用変数
    float x_speed;      //Xのスピード
    float y_speed;      //Yのスピード
    double direction;    //進行方向
    
    //描画用変数
    int images[9];      //画像
    int images_index;
    int frame_count;

public:

    //コンストラクタ
    WyvernBless(const Location, const Location);

    //デストラクタ
    ~WyvernBless();

    //更新
    void Update() override;

    //描画
    void Draw() const override;

};

