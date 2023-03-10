#include "BulletManager.h"
#include "Stage/Stage.h"
#include "CameraWork.h"

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
void BulletManager::Update(const Stage* stage)
{
    for (int i = 0; i < enemy_bullet_count; i++)
    {
        if (enemy_bullets[i] == nullptr)
        {
            break;
        }

        enemy_bullets[i]->Update();

        if (enemy_bullets[i]->ScreenOut() || enemy_bullets[i]->HitStage(stage)) //画面外に出たか
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
            enemy_bullet_count--;
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
        if (enemy_bullets == nullptr)
        {
            //最大値の更新
            enemy_bullet_max += ENEMY_BULLET_EXPANSION;

            enemy_bullets = new EnemyBulletBase * [enemy_bullet_max];
            for (int i = 0; i < enemy_bullet_max; i++)
            {
                enemy_bullets[i] = nullptr;
            }
        }
        else
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
            for (int i = enemy_bullet_count; i < enemy_bullet_max; i++)
            {
                enemy_bullets[i] = nullptr;
            }
        }
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
    }
}

//-----------------------------------
//弾の削除
//-----------------------------------
void BulletManager::DeleteEnemyBullet(const EnemyBulletBase* bullet)
{
    for (int i = 0; i < enemy_bullet_max; i++)
    {
        if (enemy_bullets[i] == bullet)
        {
            delete enemy_bullets[i];
            enemy_bullets[i] = nullptr;

            SortEnemyBullet(i);
            enemy_bullet_count--;
            break;
        }
    }
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource BulletManager::Hit(const int i)
{
    AttackResource ret = { 0,nullptr,0 }; //戻り値

    ENEMY_TYPE attack_type[1] = { enemy_bullets[i]->GetType() };
    ret.damage = enemy_bullets[i]->GetDamage();
    ret.type = attack_type;
    ret.type_count = 1;

    return ret;
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

//-----------------------------------
//弾の最大値の取得
//-----------------------------------
int BulletManager::EnemyGetBulletMax() const
{
    return enemy_bullet_max;
}