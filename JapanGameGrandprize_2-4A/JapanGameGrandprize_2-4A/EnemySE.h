#pragma once
#include "EnemyKind.h"

struct NomalEnemySE
{
    int move; //移動
    int attack; //攻撃
};
class EnemySE
{
private:
   static NomalEnemySE slime_se;  //スライムSE
   static NomalEnemySE undead_se; //アンデットSE
   static NomalEnemySE harpy_se; //ハーピィSE
   static NomalEnemySE mage_se; //メイジSE
   static NomalEnemySE ghost_se; //ゴーストSE
   static NomalEnemySE wyvern_se; //ワイバーンSE

   static int down_se; //ダウン時SE


private:
    EnemySE() = default;

public:

	~EnemySE();

    //サウンドの読み込み
    static void LoadSound();

    //サウンドの削除
    static void DeleteSound();

    //通常エネミーのSEの取得
    static NomalEnemySE GetEnemySE(const ENEMY_KIND);
};

