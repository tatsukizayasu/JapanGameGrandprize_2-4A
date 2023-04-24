#pragma once
#include "EnemyBase.h"


enum class HAND_MOVE
{
    UP_DOWN = 0, //上下移動
    CIRCULAR_MOTION, //円状移動
    NONE
};

class LastBossHand :
    public EnemyBase
{
private:

    bool punch;  //パンチしている
    bool left_hand; //true:左手,false:右手
    bool attack; //攻撃が当たったか
    int move_volume; //移動量
    int angle; //角度
    int radius; //半径
    int attack_interval; //次の攻撃までの時間
    int punch_standby_time; //パンチするまでの時間
    int animation; //アニメーション
    int image_argument; //画像の引数
    int death_time; //死んでいる時間

    Location spawn_location; //生成地点
    Location punch_start; //パンチを始めたの座標

    HAND_MOVE move; //移動方法

    HitMapChip hit_block; //ブロックとの当たり判定
private:

    //テレポート
    void Teleport(const class Stage* stage);

    //パンチ
    void Punch();

    //移動時のアニメーション
    void MoveAnimation();
public:

    //コンストラクタ
    LastBossHand(const Location, const bool);

    //デストラクタ
    ~LastBossHand();

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

    //描画
    void Draw() const override;

    //HPバーの表示
    void DrawHPBar(const int)const override;

    //座標の取得
    Location GetLocation() const override;

#ifdef _DEBUG
    //更新(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //描画(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG

};

