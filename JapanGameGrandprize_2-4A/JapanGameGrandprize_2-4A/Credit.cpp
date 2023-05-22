#include "Credit.h"
#include"DxLib.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Credit::Credit()
{
	display_time = 0;
	time = 0;
	cr = GetColor(255, 255, 255); 
}


//-----------------------------------
// デストラクタ
//-----------------------------------
Credit::~Credit()
{

}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* Credit::Update()
{
	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void Credit::Draw()const
{

	/*
	* DrawStirng(100,100,"使用したSE、BGM",cr);
	DrawString(100,150,"無料効果音で遊ぼう！",cr);
	DrawString(100,200,"DOVA-SYNDROME",cr);
	DrawString(100,250,"フリー効果音素材 くらげ工匠",cr);
	DrawString(100,300,"TAM Music Factory",cr);

	*/
}