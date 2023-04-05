#include "GameOver.h"
#include "GameMain.h"
#include "PadInput.h"
#include "DxLib.h"

GameOver::GameOver()
{

}

AbstractScene* GameOver::Update()
{

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y))
	{
		return new GameMain();
	}

	return this;
}

void GameOver::Draw()const
{

	DrawString(0, 0, "GameOver", 0xFFFFFF);
}