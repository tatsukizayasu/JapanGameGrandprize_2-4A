#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"

class Torrent :
    public EnemyBase
{
private:

public:

    //コンストラクタ
    Torrent();

    //デストラクタ
    ~Torrent();

    //更新
    void Update(const class Player* player, const class Stage* stage) override;

    //アイドル状態
    void Idol() override;

    //移動
    void Move(const Location player_location) override;

    //落下
    void Fall() override;

    //攻撃
    void  Attack(Location) override;

    //攻撃が当たっているか
    AttackResource Hit() override;

    //死亡
    void Death() override;

    //プレイヤーの弾との当たり判定
    void HitBullet(const BulletBase* bullet) override;

    //描画
    void Draw() const override;

    //座標の取得
    Location GetLocation() const override;
};