#pragma once

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
	GOLEM,		//ゴーレム
	DRAGON,		//ドラゴン
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
	EnemyBase();

	//デストラクタ
	~EnemyBase() {};

	//描画以外の更新を実行
	virtual void Update() = 0;

	//描画
	virtual void Draw() const = 0;

	//HPが0かどうか判断(0になったらtrue)
	bool CheckHp()
	{
		bool ret = false;
		if (hp < 0)
		{
			ret = true;
		}
		return ret;
	}

protected:
	int hp;	//体力
	int speed; //移動速度

	ENEMY_KIND kind; //エネミーの種類
	ENEMY_TYPE type; //エネミーのタイプ
};

