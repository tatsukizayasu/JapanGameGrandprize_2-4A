#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "Player.h"

enum class UNDEAD_STATE
{
    IDOL,   //アイドル状態
    MOVE,   //移動
    ATTACK, //攻撃
    DEATH,  //死亡
};

class Undead :
    public EnemyBase, public BoxCollider
{
private:
    int damage; //ダメージ
    int attack_interval; //次の攻撃までの時間
    int attack; //攻撃している
    int image; //画像
    int attack_time; //攻撃している時間(デバッグ用)
    ENEMY_TYPE attack_type; //攻撃の属性
    UNDEAD_STATE state; //状態

    Player* player; //プレイヤー
private:
    //プレイヤーとの距離
    void DistancePlayer();
public:
    //コンストラクタ
    Undead(Player* player);

    //デストラクタ
    ~Undead();

    //描画以外の更新
    void Update() override;

    //プレイヤーの弾との当たり判定
    void HitBullet(BulletBase* bullet) override;

    //描画
    void Draw() const override;

    //状態の取得
    UNDEAD_STATE GetState() const;
};

