#include "Pause.h"
#include "DxLib.h"
#include "PadInput.h"

Pause::Pause()
{

	is_paused = false;
	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	pause_graph = 0;
	pause_effect_timer = 0;

	cursor_osition = 0;
}

Pause::~Pause()
{

	DeleteFontToHandle(title_font);
	DeleteGraph(pause_graph);
}

void Pause::Update()
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

	//ポーズ時徐々にぼかす
	if (pause_effect_timer < 50 && is_paused == true)
	{
		pause_effect_timer++;
		if (pause_effect_timer % 5 == 0) 
		{
			GraphFilter(pause_graph, DX_GRAPH_FILTER_GAUSS, 16, 70);
		}
	}

	if (is_paused && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) 
	{

		next_menu = 1;
	}
}

void Pause::Draw() const
{

	DrawGraph(0, 0, pause_graph, FALSE);

	DrawStringToHandle(GetDrawCenterX("ポーズ", title_font), 100, "ポーズ", 0xF4948E, title_font, 0x000000);

	DrawStringToHandle(GetDrawCenterX("リスタート", menu_font), 300, "リスタート", 0xF4058E, menu_font, 0x000000);
}

int Pause::GetDrawCenterX(const char* string, int font_handle)const 
{

	//画面幅
	const int screenX = 1280;

	const int w = screenX / 2 - GetDrawFormatStringWidthToHandle(font_handle, string) / 2;
	return w;
}