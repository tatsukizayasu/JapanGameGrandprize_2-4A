#pragma once
#include "EnemyBase.h"


enum class WYVERN_ATTACK
{
    BLESS,          //ブレス
    TRIPLE_BRACE,   //3連ブレス
    ASSAULT,        //強襲攻撃
    NONE
};

class Wyvern :
    public EnemyBase
{
private:
    bool attack_end; //攻撃が終わった
    bool attack; //攻撃が当たったか
    bool now_assault; //強襲攻撃かどうか
    int damage; //ダメージ
    int bless_interval;         //次のブレス攻撃までの時間
    int triple_bless_interval;  //次の3連ブレス攻撃までの時間
    int assault_interval;       //次の強襲攻撃までの時間
    int shot_rate;  //ブレスの発射レート
    int shot_count; //発射した弾の数
    Location assault_start;     //強襲攻撃のスタート位置
    Location assault_speed;     //強襲攻撃のスピード
    int image_argument; //画像の引数

    WYVERN_ATTACK attack_state; //攻撃
    HitMapChip hit_stage;
private:

    //移動時のアニメーション
    void MoveAnimation();

    //ブレス
    void Bless(const Location);

    //トリプルブレス
    void TripleBless(const Location);

    //強襲攻撃
    void Assault(const Location);

    // 攻撃していない
    void AttackNone();
public:

    //コンストラクタ
    Wyvern(Location);

    //デストラクタ
    ~Wyvern();

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

    //座標の取得
    Location GetLocation() const override;

#ifdef _DEBUG
    //更新(DotByDot)
    void Update(const ENEMY_STATE state) override;

    //描画(DotByDot)
    void DebugDraw() override;
#endif //_DEBUG

};

