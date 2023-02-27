#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Player.h"

class Undead :
    public EnemyBase, public BoxCollider
{
private:

    int damage; //ダメージ
    int attack_interval; //次の攻撃までの時間
    int image; //画像
    int attack_time; //攻撃している時間(デバッグ用)
private:

    //プレイヤーとの距離
    void DistancePlayer(const Location player_location);
public:

    //コンストラクタ
    Undead();

    //デストラクタ
    ~Undead();

    //描画以外の更新
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