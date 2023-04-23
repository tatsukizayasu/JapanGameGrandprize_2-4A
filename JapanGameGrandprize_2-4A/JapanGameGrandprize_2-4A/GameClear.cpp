#include "GameClear.h"
#include "GameMain.h"
#include "PadInput.h"
#include "DxLib.h"

GameClear::GameClear(short stage_num)
{
	title_font = CreateFontToHandle("UD ƒfƒWƒ^ƒ‹ ‹³‰È‘‘Ì N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	this->stage_num = stage_num;
}

GameClear::~GameClear()
{
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
	DrawStringToHandle(GetDrawCenterX("GameClear", title_font), 150, "GameClear", 0xffffff,title_font);
	DrawStringToHandle(GetDrawCenterX("Press A Button", title_font), 500, "Press A Button", 0xffffff, title_font);
	
}
