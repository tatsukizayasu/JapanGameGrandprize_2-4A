#pragma once
#include "EnemyBulletBase.h"
class TorrentNuts :
    public EnemyBulletBase
{
private:

    int image; //画像
public:

    //コンストラクタ
    TorrentNuts(ENEMY_TYPE, Location);

    //デストラクタ
    ~TorrentNuts();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};