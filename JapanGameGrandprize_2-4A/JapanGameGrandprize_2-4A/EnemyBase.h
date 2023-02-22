#pragma once
#include "Define.h"
#include "Bullet.h"
#include "ElementItem.h"
#include "EnumEnemyType.h"

//各属性のドロップ数
#define FIRE_DROP 3
#define WATER_DROP 4
#define WIND_DROP 3
#define SOIL_DROP 4
#define THUNDER_DROP 7

//ダメージ倍率
#define WEAKNESS_DAMAGE 2.0f
#define RESISTANCE_DAMAGE 0.5f

//デバフの効果時間の倍率
#define WEAKNESS_DEBUFF 1.5f
#define	RESISTANCE_DEBUFF 0.5f

//毒ダメージを受けるまでのフレーム数
#define POISON_DAMAGE_FLAME 10

//麻痺状態の移動スピードの倍率
#define PARALYSIS_SPEED 0.7f

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

struct AttackResource
{
	int damage; //ダメージ
	ENEMY_TYPE* type; //攻撃タイプ
	int type_count; //攻撃タイプの数
};

enum class ENEMY_STATE
{
	IDOL,   //アイドル状態
	MOVE,   //移動
	ATTACK, //攻撃
	DEATH,  //死亡
};

class EnemyBase
{
public:
	//コンストラクタ
	EnemyBase();

	//デストラクタ
	~EnemyBase() {}

	//描画以外の更新を実行
	virtual void Update() = 0;

	//描画
	virtual void Draw() const = 0;

	//アイドル状態
	virtual void Idol() = 0;

	//移動
	virtual void Move(const Location player_location) = 0;

	//攻撃
	virtual AttackResource Attack(const BoxCollider* collider) = 0;

	//死亡
	virtual void Death() = 0;

	
	//プレイヤーの弾との当たり判定
	virtual void HitBullet(const BulletBase* bullet) = 0;

	//ドロップする種類の量の取得
	int GetDropTypeVolume() const;

	//ドロップするアイテムの量の取得
	int GetDropVolume()const;

	//ドロップアイテムの取得
	ElementItem GetDropItem(int i) const;

	//エネミーの種類の取得
	ENEMY_KIND GetEnemyKind() const;

	//エネミーの状態の取得
	ENEMY_STATE GetState()const;

	//削除可能状態の取得
	bool GetCanDelete() const;

protected:
	bool can_delete; //削除フラグ
	int hp;	//体力
	int speed; //移動速度
	int poison_time; //毒の効果時間
	float poison_damage; //毒のダメージ
	int paralysis_time; //麻痺の効果時間

	int drop_volume; //ドロップ量
	int drop_type_volume; //ドロップする種類の量
	ElementItem** drop_element; //ドロップ元素

	ENEMY_KIND kind; //エネミーの種類
	ENEMY_TYPE* type; //エネミーのタイプ
	ENEMY_STATE state; //エネミーの状態
protected:
	//HPが0かどうか判断(0になったらtrue)
	bool CheckHp();

	//毒状態の処理
	void Poison();

	//麻痺状態の処理
	void Paralysis();
};