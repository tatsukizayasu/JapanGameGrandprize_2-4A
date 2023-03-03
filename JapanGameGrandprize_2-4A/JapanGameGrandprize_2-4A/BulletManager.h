#pragma once
#include "EnemyBulletBase.h"

class BulletManager
{
    // シングルトン
private:
    //コンストラクタ
    BulletManager();
    static BulletManager* instance; //インスタンス

public:
    //インスタンスの取得
    static BulletManager* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new BulletManager();
        }

        return instance;
    }
    // シングルトン　ここまで

private:
    class EnemyBulletsBase** enemy_bullets;
    int enemy_bullet_count;
    int enemy_bullet_max;

public:
    //デストラクタ
    ~BulletManager();

    //更新
    void Update();

    //弾の生成
    void CreateEnemyBullet(class EnemyBulletsBase* bullet);

    //弾の並べ替え
    void SortEnemyBullet(int bullet_num);

    //弾の削除
    EnemyBulletsBase** DeletePlayerBullet(EnemyBulletsBase* bullet);

    //描画
    void Draw();

    //弾の取得
    EnemyBulletsBase** GetPlayerBullets();

};

