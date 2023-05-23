#pragma once
#include "EnemyBulletBase.h"

class TorrentBullet :
    public EnemyBulletBase
{
private:

    int* images; //画像
    int image; //描画用の画像
    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
    int angle;
public:

    //コンストラクタ
    TorrentBullet(const Location, const Location);

    //デストラクタ
    ~TorrentBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};