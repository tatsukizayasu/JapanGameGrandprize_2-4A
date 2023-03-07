#pragma once

//プレイヤーが持っている元素の種類
#define PLAYER_ELEMENT 7

#define SCREEN_HEIGHT 720	//画面サイズ (縦)
#define SCREEN_WIDTH 1280	//画面サイズ (横)
#define GRAVITY 10

//化合物構造体
struct Compound
{
	int warter;				//水
	int carbon_dioxide;		//二酸化炭素
	int ozone;				//オゾン
	int sulfuric_acid;		//硫酸
	int hydrochloric_acid;	//塩酸
	int alcohol;			//アルコール
	int tear_gas;			//催涙ガス
	int suger;				//砂糖
	int ammonium_chloride;  //塩化アンモニウム
	int acetic_acid;		//酢酸
	int propane;			//プロパン
	int uranium;			//ウラン
};

enum class ATTRIBUTE
{
	NORMAL = 0,
	EXPLOSION,
	MELT,
	POISON,
	PARALYSIS,
	HEAL
};

//中心座標
struct Location
{
	float x;	//中心座標(x)
	float y;	//中心座標(y)

	Location operator +(Location location)
	{
		Location ret;

		ret.x = this->x + location.x;
		ret.y = this->y + location.y;

		return ret;
	}

	Location operator -(Location location)
	{
		Location ret;

		ret.x = this->x - location.x;
		ret.y = this->y - location.y;

		return ret;
	}
};

//サイズ
struct Area
{
	float height;	//縦
	float width;	//横
};

