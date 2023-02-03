#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"

enum class UNDEAD_STATE
{
    IDOL,   //アイドル状態
    MOVE,   //移動
    ATTACK, //攻撃
    DEATH,  //死亡
};

class Undead :
    public EnemyBase
{
private:
    int damage; //ダメージ
    Location location; //中心座標
    UNDEAD_STATE state; //状態
    BoxCollider collider; //当たり判定
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

    //描画
    void Draw() const override;
};

