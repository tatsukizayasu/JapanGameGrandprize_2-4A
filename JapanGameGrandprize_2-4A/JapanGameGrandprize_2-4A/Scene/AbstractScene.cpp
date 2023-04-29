#include "AbstractScene.h"
#include "DxLib.h"

AbstractScene::~AbstractScene()
{
		DeleteFontToHandle(title_font);
}

int AbstractScene::GetDrawCenterX(const char* string, int font_handle)const
{

	//âÊñ ïù
	const int screenX = 1280;

	const int w = screenX / 2 - GetDrawFormatStringWidthToHandle(font_handle, string) / 2;
	return w;
}