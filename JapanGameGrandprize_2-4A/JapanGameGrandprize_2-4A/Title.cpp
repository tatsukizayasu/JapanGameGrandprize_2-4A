#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include"PadInput.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 120, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	background_image = 0;

	bgm = 0;
	select_se = 0;
	decision_se = 0;

	input_margin = 0;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Title::~Title()
{
	DeleteFontToHandle(title_font);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* Title::Update()
{
	//シーン切り替えテスト		デバック
	if (CheckHitKey(KEY_INPUT_Z) && input_margin >= 30) 
	{
		input_margin = 0;
		return new GameMain();
	}

	if (input_margin < 30) 
	{
		input_margin++;
	}

	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void Title::Draw()const
{
	DrawStringToHandle(GetDrawCenterX("タイトル",title_font), 100, "タイトル", 0x56F590, title_font, 0xFFFFFF);
}

//-----------------------------------
// 画面の中心をとる
//-----------------------------------
int Title::GetDrawCenterX(const char* string, int font_handle, int margin)const
{

	//画面幅
	const int screenX = 1280;

	if (margin >= screenX || margin <= -screenX)
	{
		margin = 0;
	}

	if (font_handle == 0) 
	{
		font_handle = DX_DEFAULT_FONT_HANDLE;
	}


	const int w = screenX / 2 + margin - (GetDrawFormatStringWidthToHandle(font_handle, string) / 2);
	return w;
}