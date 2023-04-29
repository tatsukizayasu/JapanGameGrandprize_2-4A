#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "DotByDot.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
	title_font = CreateFontToHandle("Algerian", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	menu_font = CreateFontToHandle("Algerian", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Images/Scene/title.png");


	select_se = 0;
	decision_se = 0;

	input_margin = 0;

#ifdef TITLE_DEBUG
	is_select_debug = false;
#endif // TITLE_DEBUG


	select_menu = static_cast<int>(MENU::PLAY);

}

//-----------------------------------
// デストラクタ
//-----------------------------------
Title::~Title()
{
	DeleteGraph(background_image);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* Title::Update()
{
	// 操作間隔時間
	const int max_input_margin = 15;

	// スティックの感度
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin)
	{
		input_margin++;
	}
	else {

		// スティックのY座標を取得
		int stick_y = PAD_INPUT::GetLStick().y;

		if (std::abs(stick_y) > stick_sensitivity) {

			// スティックが上に移動した場合
			if (stick_y > 0) {
				// メニュー選択肢を一つ前に移動
				select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
			}
			// スティックが下に移動した場合
			else if (stick_y < 0) {
				// メニュー選択肢を一つ次に移動
				select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
			}

			input_margin = 0;

		}

#ifdef TITLE_DEBUG
		if (std::abs(PAD_INPUT::GetLStick().x) > stick_sensitivity) {

			is_select_debug = !is_select_debug;
			input_margin = 0;

		}
#endif // TITLE_DEBUG

	}


	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
#ifdef TITLE_DEBUG
		if (is_select_debug == true) {
			return new DotByDot();
		}
#endif // TITLE_DEBUG


		input_margin = 0;
		MENU current_selection = static_cast<MENU>(select_menu);
		switch (current_selection)
		{
		case Title::MENU::PLAY:
			return new GameMain(1);
			break;

		case Title::MENU::EXIT:
			return nullptr;
			break;

		default:
			printfDx("未実装な機能です。\n");
			break;
		}

	}



	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void Title::Draw()const
{
	DrawGraph(0, 0, background_image, FALSE);
	DrawStringToHandle(GetDrawCenterX("Elemental War", title_font), 100, "Elemental War", 0x66290E, title_font, 0xFFFFFF);

	for (int i = 0; i < static_cast<int>(MENU::MENU_SIZE); i++)
	{
		// 文字列の最小Y座標
		const int base_y = 400;

		// 文字列のY座標間隔
		const int margin_y = 100;

		// 文字色
		int color = 0xFFFFFF;
		// 文字外枠色
		int border_color = 0x000000;

#ifdef TITLE_DEBUG

		// 文字色
		int debug_color = 0xFFFFFF;
		// 文字外枠色
		int debug_border_color = 0x000000;

		if (is_select_debug == true) {
			debug_color = ~color;
			debug_border_color = ~border_color;
		}else if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}

		DrawStringToHandle(100, 600, "DEBUG", debug_color, menu_font, debug_border_color);

#else

		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}

#endif // TITLE_DEBUG

		DrawStringToHandle(GetDrawCenterX(menu_items[i], menu_font), i * margin_y + base_y, menu_items[i], color, menu_font, border_color);
	}


}