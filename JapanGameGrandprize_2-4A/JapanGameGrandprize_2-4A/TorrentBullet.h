#pragma once
#include "EnemyBulletBase.h"

class TorrentBullet :
    public EnemyBulletBase
{
private:

    int image; //画像
    int x_speed; //Xのスピード
    int y_speed; //Yのスピード
public:

    //コンストラクタ
    TorrentBullet(ENEMY_TYPE, Location, Location);

    //デストラクタ
    ~TorrentBullet();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};