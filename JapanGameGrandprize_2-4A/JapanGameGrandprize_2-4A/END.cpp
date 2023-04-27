#include "END.h"
#include "DxLib.h"
#include "Title.h"
#include "PadInput.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
END::END()
{
	title_font = CreateFontToHandle("Algerian", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	menu_font = CreateFontToHandle("Algerian", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	background_image = LoadGraph("Images/Scene/end.png");


	select_se = 0;
	decision_se = 0;

	input_margin = 0;

	select_menu = 0;

	top_menu[0] = { 0,"TITLE" };
	top_menu[1] = { 1, "EXIT" };
}

//-----------------------------------
// デストラクタ
//-----------------------------------
END::~END()
{
	DeleteFontToHandle(title_font);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* END::Update()
{

	if (input_margin < 30)
	{
		input_margin++;
	}
	else {


		if (PAD_INPUT::GetLStick().y > 20000)
		{
			select_menu = (select_menu + 1) % 2;
			input_margin = 0;
		}
		else if (PAD_INPUT::GetLStick().y < -20000)
		{

			select_menu = (select_menu + 1) % 2;
			input_margin = 0;
		}
	}


	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		input_margin = 0;
		switch (select_menu)
		{
			// TITLE
		case 0:
			return new Title();
			break;

			// EXIT
		case 1:
			DxLib_End();
			break;

		default:
			break;
		}

	}



	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void END::Draw()const
{
	DrawGraph(0, 0, background_image, FALSE);
	DrawStringToHandle(GetDrawCenterX("Thanks!", title_font), 100, "Thanks!", 0x66290E, title_font, 0xFFFFFF);

	for (int i = 0; i < 2; i++)
	{
		// 文字色
		int color = 0xFFFFFF;
		// 文字外枠色
		int border_color = 0x000000;

		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (select_menu == top_menu[i].number) {
			color = ~color;
			border_color = ~border_color;
		}

		DrawStringToHandle(GetDrawCenterX(top_menu[i].string.c_str(), menu_font), i * 100 + 400, top_menu[i].string.c_str(), color, menu_font, border_color);
	}


}