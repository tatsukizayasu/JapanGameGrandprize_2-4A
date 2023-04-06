#pragma once
#include "EnemyBulletBase.h"
class WyvernBless :
    public EnemyBulletBase
{
private:

    int image; //画像
    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
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

