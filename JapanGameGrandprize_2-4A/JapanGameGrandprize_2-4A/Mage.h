#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"
#include "MageBullet.h"

#define MAGE_BULLET_MAX 20

class Mage :
    public EnemyBase,public BoxCollider
{
private:
    int shot_rate; //魔法弾の発射レート
    int shot_count; //発射した弾の数
    int image; //画像
    int drop; //ドロップするアイテムの種類の数
    Player* player; //プレイヤー

    MageBullet* bullet[20]; //弾

private:
    //弾の生成
    void CreateBullet();

    //弾の並び替え
    void SortBullet(int);
public:

    //コンストラクタ
    Mage();

    //デストラクタ
    ~Mage();

    //更新
    void Update() override;

    //アイドル状態
    void Idol() override;

    //移動
    void Move(const Location player_location) override;

    //攻撃
    void  Attack() override;

    //攻撃が当たっているか
    AttackResource HitCheck(const BoxCollider* collider) override;

    //死亡
    void Death() override;

    //プレイヤーの弾との当たり判定
    bool HitBullet(const BulletBase* bullet) override;

    //描画
    void Draw() const override;

    //弾の取得
    MageBullet GetBullet(int) const;

    //座標の取得
    Location GetLocation() const override;
};

