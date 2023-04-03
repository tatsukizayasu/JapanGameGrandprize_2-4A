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
    int damage; //ダメージ
    int bless_interval;         //次のブレス攻撃までの時間
    int triple_bless_interval;  //次の3連ブレス攻撃までの時間
    int assault_interval;       //次の強襲攻撃までの時間
    int shot_rate;  //ブレスの発射レート
    int assault_speed[2];   //強襲攻撃のスピード(0 : X , 1 : Y)
    int image_argument; //画像の引数

    WYVERN_ATTACK attack_state; //攻撃
private:

    //移動時のアニメーション
    void MoveAnimation();

    //ブレスの生成
    void CreateBless(const Location);

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

