#pragma once
#include "AbstractScene.h"
#include "Define.h"
#include "ColliderBase.h"


enum class CHARACTER
{
    Player,
    SLIME,	    //スライム
    UNDEAD,		//アンデット
    HARPY,		//ハーピィ
    MAGE,		//メイジ
    GHOST,		//ゴースト
    WYVERN,		//ワイバーン
    SLIME_BOSS, //スライムキング
    TORRENT,	//トレント
    GARGOYLE,	//ガーゴイル
    DRAGON,		//ドラゴン
    END_BOSS,	//ラスボス
};

enum class BLOCK
{

};

//ドットバイドット用の構造体
struct Character
{
    Location location;      //座標
    Area area;              //当たり判定
    int* images;            //画像
    CHARACTER type;         //タイプ
};

//ドットバイドット用の構造体
struct Block
{
    Location location;      //座標
    Area area;              //当たり判定
    int* images;            //画像
    Character type;         //タイプ
};
//ドットバイドット用の構造体
struct DebugBullet
{
    Location location;      //座標
    int radius;              //当たり判定
    int* images;            //画像
};

class DotByDot :
    public AbstractScene
{
private:
    //キャラクター用
    Character* character;

    //弾用
    DebugBullet* bullet;

    //ブロック用
    Block* block;
public:
    //コンストラクタ
    DotByDot();

    //デストラクタ
    ~DotByDot();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;
};

