#include "Pause.h"
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "../PadInput.h"


Pause::Pause()
{

	is_paused = false;
	title_font = CreateFontToHandle("Algerian", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("Algerian", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	if ((enter_se = LoadSoundMem("Sounds/SE/enter.mp3")) == -1) {
		throw "Sounds/SE/enter.mp3";
	}

	if ((cursor_move_se = LoadSoundMem("Sounds/SE/cursor_move.mp3")) == -1)
	{
		throw "Sounds/SE/cursor_move.mp3";
	}

	pause_graph = 0;
	pause_effect_timer = 0;

	next_scene = -1;
	select_menu = static_cast<int>(MENU::RETURN);
	input_margin = 0;

	cursor_osition = 0;
}

Pause::~Pause()
{
	DeleteGraph(pause_graph);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteSoundMem(enter_se);
	DeleteSoundMem(cursor_move_se);
}

void Pause::Update(short stage_num)
{
		
	//ウィジェットが非アクティブ、ウィンドウが最小化された場合にポーズ
	if (GetWindowActiveFlag() == FALSE || GetWindowMinSizeFlag() == TRUE) 
	{
		if (pause_graph == 0)
		{
			pause_graph = MakeGraph(1280, 720);
			GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);
		}
		is_paused = true;
	}

	//STARTボタンでポーズ切り替え
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) 
	{
		TogglePause();
	}

	//ポーズ時徐々にぼかす
	if (pause_effect_timer < 50 && is_paused == true)
	{
		pause_effect_timer++;
		if (pause_effect_timer % 5 == 0) 
		{
			GraphFilter(pause_graph, DX_GRAPH_FILTER_GAUSS, 16, 70);
		}
	}


	//メニュー操作
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

				PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);

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
		}


		if (is_paused && PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnRelease(XINPUT_BUTTON_A) == true))
		{
			PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
			while (CheckSoundMem(enter_se)) {}

			input_margin = 0;

			next_scene = static_cast<short>(select_menu);

			if (next_scene == 0)
			{
				next_scene = -1;
				TogglePause();
			}

		}
	}
}

void Pause::Draw() const
{

	DrawGraph(0, 0, pause_graph, FALSE);

	DrawStringToHandle(GetDrawCenterX("PAUSE", title_font), 100, "PAUSE", 0xF4948E, title_font, 0x000000);
	//DrawStringToHandle(GetDrawCenterX("Game Over", title_font), 150, "Game Over", 0xFFFFFF, title_font, 0x000000);

	for (int i = 0; i < static_cast<int>(MENU::MENU_SIZE); i++)
	{
		// 文字列の最小Y座標
		const int base_y = 300;

		// 文字列のY座標間隔
		const int margin_y = 100;

		// 文字色
		int color = 0xFFFFFF;
		// 文字外枠色
		int border_color = 0x000000;
		// 透明度
		int transparency = 180;

		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
			transparency = 255;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawStringToHandle(GetDrawCenterX(menu_items[i], menu_font), i * margin_y + base_y, menu_items[i], color, menu_font, border_color);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Pause::TogglePause()
{
	if (pause_graph == 0)
	{
		pause_graph = MakeGraph(1280, 720);
		GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);
	}
	else
	{
		DeleteGraph(pause_graph);
		pause_graph = 0;
		pause_effect_timer = 0;
	}
	is_paused = !is_paused;
}

int Pause::GetDrawCenterX(const char* string, int font_handle)const
{

	//画面幅
	const int screenX = 1280;

	const int w = screenX / 2 - GetDrawFormatStringWidthToHandle(font_handle, string) / 2;
	return w;
}