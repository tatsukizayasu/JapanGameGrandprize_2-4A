#pragma once
#include "EnemyBase.h"

enum class LAST_BOSS_ATTACK
{
    MAGIC = 0,      //魔法攻撃
    PUNCH,          //パンチ
    SWORD,          //剣での攻撃
    SPECIAL_MOVES,  //必殺
    NONE
};

class LastBoss :
    public EnemyBase
{
private:
    bool special_moves; //必殺技をしたか
    bool down; //ダウン
    bool attack; //攻撃が当たったか
    int down_time; //ダウンしている時間
    int attack_interval; //次の攻撃までの時間
    int magic_interval; //次の魔法攻撃までの時間
    int punch_interval; //次のパンチ攻撃までの時間
    int sword_interval; //剣攻撃までの時間
    int magic_rate; //魔法攻撃のレート
    int special_moves_time; //必殺技の時間
    int animation; //アニメーション
    int image_argument; //画像の引数
    int attack_time; //攻撃している時間

    Location spawn_location; //スポーン座標
    EnemyBase** hand; //手

    HitMapChip hit_stage; //ステージとの当たり判定

    LAST_BOSS_ATTACK attack_state; //攻撃
private:

    //移動時のアニメーション
    void MoveAnimation();

    //ダウンからの復帰
    bool Revival();

    //魔法攻撃の初期化
    void InitMagic();

    //魔法攻撃
    void Magic();

    //パンチ攻撃の初期化
    void InitPunch();

    //パンチ攻撃
    void Punch();

    //剣攻撃の初期化
    void InitSword();

    //剣攻撃
    void Sword();

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

    //HPバーの描画
    void DrawHPBar(const int) const;

    //座標の取得
    Location GetLocation() const override;


#ifdef _DEBUG
    //更新(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //描画(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG
};