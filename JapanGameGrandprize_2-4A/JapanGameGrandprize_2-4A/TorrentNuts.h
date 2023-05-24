#pragma once
#include "EnemyBulletBase.h"
class TorrentNuts :
    public EnemyBulletBase
{
private:

    int images[3]; //画像
    int argument; //描画画像
public:

    //コンストラクタ
    TorrentNuts(const ENEMY_TYPE, const Location);

    //デストラクタ
    ~TorrentNuts();

    //更新
    void Update() override;

    //描画
    void Draw() const override;
};