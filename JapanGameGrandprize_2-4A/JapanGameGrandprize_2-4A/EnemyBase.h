#pragma once
#include "Define.h"
#include "Bullet.h"
#include "ElementItem.h"
#include "Item.h"

//エネミーの種類
enum class ENEMY_KIND
{
	/*雑魚敵*/
	SLIME = 0,	//スライム
	UNDEAD,		//アンデット
	HARPY,		//ハーピィ
	MAGE,		//メイジ
	GHOST,		//ゴースト
	WYVERN,		//ワイバーン

	/*ボス*/
	KING_SLIME, //スライムキング
	TORRENT,	//トレント
	GARGOYLE,	//ガーゴイル
	DRAGON,		//ドラゴン
	END_BOSS,	//ラスボス
	NONE
};

//属性
enum class ENEMY_TYPE
{
	NORMAL = 0,	//無属性
	FIRE,		//火属性
	WATER,		//水属性
	WIND,		//風属性
	SOIL,		//土属性
	THUNDER,	//雷属性
};

class EnemyBase
{
public:
	//コンストラクタ
	EnemyBase() {};

	//デストラクタ
	~EnemyBase() {};

	//描画以外の更新を実行
	virtual void Update() = 0;

	//描画
	virtual void Draw() const = 0;

	//プレイヤーの弾との当たり判定
	virtual void HitBullet(Bullet* bullet) = 0;

	//ドロップアイテムの取得
	ElementItem GetDropItem(int i) const;

	//エネミーの種類の取得
	ENEMY_KIND GetEnemyKind() const;

protected: 
	int hp;	//体力
	int speed; //移動速度

	int drop_volume; //ドロップ量

	ElementItem** drop_element; //ドロップ元素
	Item** drop_item; //ドロップアイテム

	ENEMY_KIND kind; //エネミーの種類
	ENEMY_TYPE* type; //エネミーのタイプ
protected:
	//HPが0かどうか判断(0になったらtrue)
	bool CheckHp();

	//アイテムの生成
	void CreateDropItem(int drop_num, Location location);

	//アイテムの並び替え
	void SortDropitem(int item_num);
};