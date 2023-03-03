#include "BulletManager.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
BulletManager::BulletManager()
{
    enemy_bullets = nullptr;
    enemy_bullet_count = 0;
    enemy_bullet_max = 0;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
BulletManager::~BulletManager()
{

}

//-----------------------------------
//更新
//-----------------------------------
void BulletManager::Update()
{

}



//-----------------------------------
//弾の生成
//-----------------------------------
void BulletManager::CreateEnemyBullet(class EnemyBulletsBase* bullet)
{

}

//-----------------------------------
//弾の並べ替え
//-----------------------------------
void BulletManager::SortEnemyBullet(int bullet_num)
{
    //弾の中身をソートする
    for (int i = bullet_num + 1; i < enemy_bullet_max; i++)
    {
        if ((enemy_bullets[i] == nullptr))
        {
            break;
        }

        enemy_bullets[i - 1] = enemy_bullets[i];
        enemy_bullets[i] = nullptr;
    }
}

//-----------------------------------
//弾の削除
//-----------------------------------
EnemyBulletsBase** BulletManager::DeletePlayerBullet(EnemyBulletsBase* bullet)
{
    for (int i = 0; i < enemy_bullet_max; i++)
    {
        if (enemy_bullets[i] == bullet)
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
        }
    }
}

//-----------------------------------
// 描画
//-----------------------------------
void BulletManager::Draw()
{

}

//-----------------------------------
//弾の取得
//-----------------------------------
EnemyBulletsBase** BulletManager::GetPlayerBullets()
{
    return enemy_bullets;
}
