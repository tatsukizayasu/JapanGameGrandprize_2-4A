#pragma once
#include "EnemyBase.h"
#include "BoxCollider.h"
#include "Player.h"

enum class TORRENT_STATE
{
    IDOL,   //アイドル状態
    MOVE,   //移動
    ATTACK, //攻撃
    DEATH,  //死亡
};
class Torrent :
    public EnemyBase,public BoxCollider
{
private:
    TORRENT_STATE state; //状態

    Player* player; //プレイヤー

public:
    //コンストラクタ
    Torrent(Player* player);

    //デストラクタ
    ~Torrent();

    //更新
    void Update() override;

    //プレイヤーの弾との当たり判定
    void HitBullet(BulletBase* bullet) override;

    //描画
    void Draw() const override;

    //状態の取得
    TORRENT_STATE GetState() const;
};

