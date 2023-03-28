#pragma once
#include "Define.h"
#include "Bullet.h"
#include "ElementItem.h"
#include "EnumEnemyType.h"
#include "BoxCollider.h"
#include "Stage/Stage.h"

//各属性のドロップ数
#define FIRE_DROP 4
#define WATER_DROP 4
#define WIND_DROP 4
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
#define PARALYSIS_SPEED 0.5f

//落下速度
#define ENEMY_FALL_SPEED 1

//当たり判定
struct HitMapChip
{
	bool hit; //当たったか
	MapChip* chip; //マップチップ
};

//ステージブロックと当たった面
enum class STAGE_DIRECTION
{
	TOP,	//上面
	BOTTOM,	//下面
	LEFT,	//左面
	RIGHT	//右面
};

//エネミーの種類
enum class ENEMY_KIND
{
	/*雑魚敵*/
	SLIME = 200,	//スライム
	UNDEAD,		//アンデット
	HARPY,		//ハーピィ
	MAGE,		//メイジ
	GHOST,		//ゴースト
	WYVERN,		//ワイバーン

	/*ボス*/
	SLIME_BOSS, //スライムキング
	TORRENT,	//トレント
	GARGOYLE,	//ガーゴイル
	DRAGON,		//ドラゴン
	END_BOSS,	//ラスボス
	NONE
};

//エネミーの状態
enum class ENEMY_STATE
{
	IDOL,   //アイドル状態
	MOVE,   //移動
	FALL,	//落下
	ATTACK, //攻撃
	DEATH,  //死亡
};

class EnemyBase :
	public BoxCollider
{
public:

	//コンストラクタ
	EnemyBase();

	//デストラクタ
	~EnemyBase() {}

	//更新
	virtual void Update(const class Player* player, const class Stage* stage) = 0;

#ifdef _DEBUG
	//更新(DotByDot)
	virtual void Update(const ENEMY_STATE state) = 0;

	//描画(DotByDot)
	virtual void DebugDraw() = 0;
#endif // _DEBUG


	

	//描画
	virtual void Draw() const = 0;

	//アイドル状態
	virtual void Idol() = 0;

	//移動
	virtual void Move(const Location player_location) = 0;

	//落下
	virtual void Fall() = 0;

	//攻撃
	virtual void  Attack(Location) = 0;

	//攻撃が当たっているか
	virtual AttackResource Hit() = 0;

	//ステージとの当たり判定
	HitMapChip HitStage(const class Stage* stage);

	//ステージのどの面と当たったを判断
	STAGE_DIRECTION HitDirection(const class MapChip* map_chip);

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

	//座標の取得
	virtual Location GetLocation() const = 0;
protected:

	bool can_delete; //削除フラグ
	bool left_move; //左に動いているかどうか
	bool poison;	//毒状態
	bool paralysis; //麻痺状態
	int* images; //画像
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

	//画面外に出た
	bool ScreenOut();

	//毒状態の処理
	void Poison();

	//麻痺状態の処理
	void Paralysis();
};