#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"

class Torrent :
    public EnemyBase,public BoxCollider
{
private:

public:
    //コンストラクタ
    Torrent();

    //デストラクタ
    ~Torrent();

    //更新
    void Update() override;

    //アイドル状態
    void Idol() override;

    //移動
    void Move(const Location player_location) override;

    //攻撃
    AttackResource Attack(const BoxCollider* collider) override;

    //死亡
    void Death() override;

    //プレイヤーの弾との当たり判定
    bool HitBullet(const BulletBase* bullet) override;

    //描画
    void Draw() const override;

    //座標の取得
    Location GetLocation() const override;
};

