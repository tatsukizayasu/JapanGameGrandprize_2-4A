#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"
#include "MageBullet.h"

#define MAGE_BULLET_MAX 20

enum class MAGE_STATE
{
    IDOL = 0, //アイドル状態
    MOVE,
    DEATH,  //死亡
};

class Mage :
    public EnemyBase,public BoxCollider
{
private:
    int shot_rate; //魔法弾の発射レート
    int image; //画像
    int drop; //ドロップするアイテムの種類の数
    MAGE_STATE state; //状態
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
    AttackResource Attack(const BoxCollider* collider) override;

    //死亡
    void Death() override;

    //プレイヤーの弾との当たり判定
    void HitBullet(const BulletBase* bullet) override;

    //描画
    void Draw() const override;

    //弾の取得
    MageBullet GetBullet(int) const;
};

