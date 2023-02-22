#include "DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];
char KeyManager::nowKey[256];
int KeyManager::oldMouse;
int KeyManager::nowMouse;

//---------------------
// 更新
//---------------------
void KeyManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];
	}
	if (GetHitKeyStateAll(nowKey) == -1)
	{
		throw - 1;
	}

	oldMouse = nowMouse;
	nowMouse = GetMouseInput();

}


//キーボード入力　引数：KEY_INPUT_anyKey

//----------------
// キークリック
//----------------
bool KeyManager::OnKeyClicked(int Key)
{
	bool ret = (oldKey[Key] != TRUE) && (nowKey[Key] == TRUE);
	return ret;
}

//----------------
// キーリリース
//----------------
bool KeyManager::OnKeyReleased(int Key)
{
	bool ret = (oldKey[Key] == TRUE) && (nowKey[Key] != TRUE);
	return ret;
}

//----------------
// キープレス
//----------------
bool KeyManager::OnKeyPressed(int Key)
{
	bool ret = (oldKey[Key] == TRUE) && (nowKey[Key] == TRUE);
	return ret;
}

//マウス入力　引数：MOUSE_INPUT_anyState

//----------------
// マウスクリック
//----------------
bool KeyManager::OnMouseClicked(int Key)
{
	bool ret = ~(oldMouse & Key) & (nowMouse & Key);
	return ret;
}

//----------------
// マウスリリース
//----------------
bool KeyManager::OnMouseReleased(int Key)
{
	bool ret = (oldMouse & Key) & ~(nowMouse & Key);
	return ret;
}

//----------------
// マウスプレス
//----------------
bool KeyManager::OnMousePressed(int Key)
{
	bool ret = (oldMouse & Key) & (nowMouse & Key);
	return ret;
}
