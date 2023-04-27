#pragma once
#include "EnemyBase.h"

enum class LAST_BOSS_ATTACK
{
    MAGIC = 0,  //魔法攻撃
    PUNCH,      //パンチ
    SWORD,      //剣での攻撃
    DEATHBLO,   //必殺
    NONE
};

class LastBoss :
    public EnemyBase
{
private:
    bool down; //ダウン
    bool attack; //攻撃が当たったか
    int down_time; //ダウンしている時間
    int attack_interval; //次の攻撃までの時間
    int animation; //アニメーション
    int image_argument; //画像の引数
    int attack_time; //攻撃している時間(デバッグ用)
    EnemyBase** hand; //手

    HitMapChip hit_stage; //ステージとの当たり判定

    LAST_BOSS_ATTACK attack_state; //攻撃
private:

    //移動時のアニメーション
    void MoveAnimation();

    //ダウンからの復帰
    bool Revival();

    //パンチ処理
    void Punch();

    //攻撃しない
    void AttackNone();
public:

    //コンストラクタ
    LastBoss(Location);

    //デストラクタ
    ~LastBoss();

    //更新
    void Update(const class Player* player, const class Stage* stage) override;

    //アイドル状態
    void Idol() override;

    //移動
    void Move(const Location player_location) override;

    //落下
    void Fall() override;

    //攻撃
    void  Attack(const Location) override;

    //攻撃が当たっているか
    AttackResource Hit() override;

    //死亡
    void Death() override;

    //プレイヤーの弾との当たり判定
    void HitBullet(const BulletBase* bullet) override;

    //プレイヤーの弾との当たり判定
    bool CheckHitBulelt(const BulletBase* bullet);

    //プレイヤーとパンチとの当たり判定
    AttackResource PunchAttack(const BoxCollider*);

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