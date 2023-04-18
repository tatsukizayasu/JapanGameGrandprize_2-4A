#pragma once
#include "EnemyBulletBase.h"
class KrakenBreath :
    public EnemyBulletBase
{
    int image; //画像

    float x_speed; //Xのスピード
    float y_speed; //Yのスピード

    int game_tiem; //時間測定 
    int start_time;//攻撃開始を測る時間 

    bool start_attack; //攻撃開始（弾が動き始める）

public:

    //コンスタラクタ
    KrakenBreath(Location, Location);

    //デストラクタ
    ~KrakenBreath();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};

