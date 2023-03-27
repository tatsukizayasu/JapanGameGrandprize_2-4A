#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "EnemyBulletBase.h"

#define MAGE_BULLET_MAX 5

class Mage :
    public EnemyBase
{
private:
    bool can_teleport; //テレポート可能か
    int teleport_count; //テレポートするまでの時間
    int teleport_rate; //テレポートのレート
    int shot_rate; //魔法弾の発射レート
    int shot_count; //発射した弾の数
    int image; //画像
    int drop; //ドロップするアイテムの種類の数
    int attack_interval; //攻撃の間隔

private:
    //テレポート
    void Teleport(const class Stage* stage);

    //弾の生成
    void CreateBullet(Location);

public:

    //コンストラクタ
    Mage(Location);

    //デストラクタ
    ~Mage();

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

#ifdef _DEBUG
    //更新(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //描画(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG
};