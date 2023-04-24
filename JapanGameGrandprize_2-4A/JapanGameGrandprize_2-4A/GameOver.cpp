#include "GameOver.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
GameOver::GameOver(short stage_num)
{
	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	this->stage_num = stage_num;
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
		//リトライ
		return new GameMain(stage_num);
	}

	return this;
}

//-----------------------------------
//描画
//-----------------------------------
void GameOver::Draw() const
{
	DrawStringToHandle(GetDrawCenterX("GameOver", title_font), 150, "GameOver", 0xffffff, title_font);
	DrawStringToHandle(GetDrawCenterX("Press A Button", title_font), 500, "Press A Button", 0xffffff, title_font);
}