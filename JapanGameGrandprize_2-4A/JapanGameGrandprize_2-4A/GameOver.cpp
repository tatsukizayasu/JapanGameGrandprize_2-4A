#include "GameOver.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
GameOver::GameOver()
{

}

//-----------------------------------
//デストラクタ
//-----------------------------------
GameOver::~GameOver()
{

}

//-----------------------------------
//更新
//-----------------------------------
AbstractScene* GameOver::Update()
{
	if(PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new GameMain();
	}

	return this;
}

//-----------------------------------
//描画
//-----------------------------------
void GameOver::Draw() const
{
	DrawString(100, 100, "GameOver", 0xffffff);
}