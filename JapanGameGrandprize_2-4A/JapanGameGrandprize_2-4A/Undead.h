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

    Location arm[2]; //腕の当たり判定
    ENEMY_TYPE attack_type; //攻撃の属性
    UNDEAD_STATE state; //状態
    LineCollider* collider; //当たり判定
private:
    //攻撃
    void Attack();

public:
    //コンストラクタ
    Undead();

    //デストラクタ
    ~Undead();

    //描画以外の更新
    void Update() override;

    //プレイヤーとの距離
    void DistancePlayer(Player* player);

    //描画
    void Draw() const override;

    //LineColliderの取得
    LineCollider GetLineCollider() const;
};

