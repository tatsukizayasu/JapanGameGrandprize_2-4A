#pragma once

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

enum class Attribute
{
	normal = 0,
	explosion,
	melt,
	poison,
	paralysis,
	heal
};

//中心座標
struct Location
{
	float x;	//中心座標(x)
	float y;	//中心座標(y)
};

//サイズ
struct Area
{
	float height;	//縦
	float width;	//横
};