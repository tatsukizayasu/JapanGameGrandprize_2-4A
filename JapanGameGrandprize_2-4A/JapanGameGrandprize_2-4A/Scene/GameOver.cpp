#include "GameOver.h"
#include "DxLib.h"
#include "GameMain.h"
#include "../PadInput.h"
#include "Title.h"
#include "../Pouch.h"

#define FADE_TIME 120

//-----------------------------------
//コンストラクタ
//-----------------------------------
GameOver::GameOver(short stage_num, unsigned int old_element_volume[PLAYER_ELEMENT], Pouch* old_pouch)
{
	title_font = CreateFontToHandle("Algerian", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("Algerian", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Images/Scene/game_over.png");

	if ((background_music = LoadSoundMem("Sounds/BGM/game_over.mp3")) == -1) {
		throw "Sounds/BGM/game_over.mp3";
	}

	if ((enter_se = LoadSoundMem("Sounds/SE/enter.mp3")) == -1) {
		throw "Sounds/SE/enter.mp3";
	}

	if ((cursor_move_se = LoadSoundMem("Sounds/SE/cursor_move.mp3")) == -1)
	{
		throw "Sounds/SE/cursor_move.mp3";
	}

	this->stage_num = stage_num;

	select_menu = static_cast<int>(MENU::RETRY);

	input_margin = 0;

	fade_counter = 0;

	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		this->old_element_volume[i] = old_element_volume[i];
	}

	this->old_pouch = old_pouch;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
GameOver::~GameOver()
{
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
	DeleteSoundMem(enter_se);
	DeleteSoundMem(cursor_move_se);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteGraph(background_image);
	SetDrawBright(255, 255, 255);
}

//-----------------------------------
//更新
//-----------------------------------
AbstractScene* GameOver::Update()
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

		if (std::abs(PAD_INPUT::GetLStick().y) > stick_sensitivity) {
			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
			select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
			input_margin = 0;

		}
	}


	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
		while (CheckSoundMem(enter_se)) {}

		input_margin = 0;
		MENU current_selection = static_cast<MENU>(select_menu);
		switch (current_selection)
		{
		case MENU::RETRY:
			return new GameMain(stage_num, old_element_volume,old_pouch);
			break;

		case MENU::TITLE:
			return new Title();
			break;

		default:
			printfDx("未実装な機能です。\n");
			break;
		}

	}

	

	if (fade_counter < FADE_TIME)
	{
		fade_counter++;
	}
	

	return this;
}

//-----------------------------------
//描画
//-----------------------------------
void GameOver::Draw() const
{

	const int fade_time = FADE_TIME;
	int bright = static_cast<int>((static_cast<float>(fade_counter) / FADE_TIME * 255));
	SetDrawBright(bright, bright, bright);

	DrawGraph(0, 0, background_image, FALSE);
	DrawStringToHandle(GetDrawCenterX("Game Over", title_font), 150, "Game Over", 0xFFFFFF, title_font, 0x000000);


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