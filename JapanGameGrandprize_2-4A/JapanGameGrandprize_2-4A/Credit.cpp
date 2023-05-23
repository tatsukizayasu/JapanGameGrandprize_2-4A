#include "Credit.h"
#include"DxLib.h"

//表示する時間
#define DISPLAY 60

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
	if (++time % 120 == 0)
	{
		if (++display_time > DISPLAY == 0)
		{
			return nullptr;
		}
	}
	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void Credit::Draw()const
{
	DrawString(100,100,"使用したSE、BGM\n",cr);
	DrawString(100,150,"無料効果音で遊ぼう！\n",cr);
	DrawString(100,200,"DOVA-SYNDROME\n",cr);
	DrawString(100,250,"フリー効果音素材 くらげ工匠\n",cr);
	DrawString(100,300,"TAM Music Factory\n",cr);
	DrawString(100,350,"効果音ラボ\n",cr);
	
}