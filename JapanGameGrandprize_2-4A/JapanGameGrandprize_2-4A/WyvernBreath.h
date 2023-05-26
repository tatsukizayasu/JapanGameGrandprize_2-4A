#pragma once
#include "EnemyBulletBase.h"
#define WYVERN_BREATH_EXTEND_RATE (0.2f)
#define WYVERN_IMAGES_NUM (9)
class WyvernBreath :
    public EnemyBulletBase
{
private:
    //移動用変数
    float x_speed;      //Xのスピード
    float y_speed;      //Yのスピード
    double direction;    //進行方向
    
    //描画用変数
    static int* images;      //画像
    int images_index;
    int frame_count;

public:

    //コンストラクタ
    WyvernBreath(const Location, const Location);

    //デストラクタ
    ~WyvernBreath();

    //更新
    void Update() override;

    //描画
    void Draw() const override;

    //画像の読み込み
    static void LoadImages();

    //画像の削除
    static void DeleteImages();

};

