#pragma once
#include"EnemyBulletBase.h"




class HarpyBullet :public EnemyBulletBase
{
private:

    int image; //画像

    int x_speed; //Xのスピード
    int y_speed; //Yのスピード

      //エフェクト
    int Tick;
    int frame;
    int PHASE;
    float angle;
    bool display_permit;

public:

    //コンスタラクタ
    HarpyBullet(const Location, const Location);

    //デストラクタ
    ~HarpyBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};