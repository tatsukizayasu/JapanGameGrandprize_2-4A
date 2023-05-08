#include "GameClear.h"
#include "GameMain.h"
#include "../PadInput.h"
#include "DxLib.h"

GameClear::GameClear(short stage_num)
{
	title_font = CreateFontToHandle("Algerian", 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	menu_font = CreateFontToHandle("Algerian", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Images/Scene/game_clear.png");

	this->stage_num = stage_num;
}

GameClear::~GameClear()
{
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteGraph(background_image);
}

AbstractScene* GameClear::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		if (stage_num < 5)
		{
			return new GameMain(stage_num + 1);
		}
		//else
		//{
		//	//return new GameEnd();
		//}
	}

	return this;
}

void GameClear::Draw() const
{
	DrawGraph(0, 0, background_image, FALSE);
	DrawStringToHandle(GetDrawCenterX("Game Clear", title_font), 150, "Game Clear", 0xFFFFFF,title_font, 0x000000);
	DrawStringToHandle(GetDrawCenterX("Next Stage", menu_font), 500, "Next Stage", 0x000000, menu_font, 0xFFFFFF);
	
}
