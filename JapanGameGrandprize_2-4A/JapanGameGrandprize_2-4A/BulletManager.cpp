#include "BulletManager.h"

BulletManager* BulletManager::instance = nullptr;

#define ENEMY_BULLET_EXPANSION 10
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
    for (int i = 0; i < enemy_bullet_max; i++)
    {
        delete enemy_bullets[i];
    }
    delete[] enemy_bullets;
}

//-----------------------------------
//更新
//-----------------------------------
void BulletManager::Update()
{
    for (int i = 0; i < enemy_bullet_count; i++)
    {
        if (enemy_bullets[i] == nullptr)
        {
            break;
        }

        enemy_bullets[i]->Update();

        if (enemy_bullets[i]->ScreenOut()) //画面外に出たか
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
        }
    }
}

//-----------------------------------
//弾の生成
//-----------------------------------
void BulletManager::CreateEnemyBullet(class EnemyBulletBase* bullet)
{
    if (enemy_bullet_count == enemy_bullet_max)
    {
        EnemyBulletBase** temporary_bullets; //避難用

        //避難
        temporary_bullets = enemy_bullets;

        //最大値の更新
        enemy_bullet_max += ENEMY_BULLET_EXPANSION;

        //弾の再生成
        enemy_bullets = new EnemyBulletBase * [enemy_bullet_max];

        //避難していた弾を戻す
        enemy_bullets = temporary_bullets;

        delete[] temporary_bullets;
    }
    //弾の生成
    enemy_bullets[enemy_bullet_count] = dynamic_cast<EnemyBulletBase*>(bullet);

    enemy_bullet_count++;

}

//-----------------------------------
//弾の並べ替え
//-----------------------------------
void BulletManager::SortEnemyBullet(const int bullet_num)
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
        enemy_bullet_count--;
    }
}

//-----------------------------------
//弾の削除
//-----------------------------------
void BulletManager::DeletePlayerBullet(const EnemyBulletBase* bullet)
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
void BulletManager::Draw() const
{
    for (int i = 0; i < enemy_bullet_count; i++)
    {
        if (enemy_bullets[i] == nullptr)
        {
            break;
        }

        enemy_bullets[i]->Draw();
    }
}

//-----------------------------------
//弾の取得
//-----------------------------------
EnemyBulletBase** BulletManager::GetEnemyBullets() const
{
    return enemy_bullets;
}
