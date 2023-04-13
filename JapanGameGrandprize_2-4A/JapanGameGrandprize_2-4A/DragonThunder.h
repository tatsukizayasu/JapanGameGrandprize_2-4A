#pragma once
#include"EnemyBulletBase.h"

class DragonThunder :
    public EnemyBulletBase
{
    int image; //画像
    int thunder_time; //雷落下待機時間
    bool attack; //攻撃開始
public:

    //コンスタラクタ
    DragonThunder(float x,float y);

    //デストラクタ
    ~DragonThunder();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};

