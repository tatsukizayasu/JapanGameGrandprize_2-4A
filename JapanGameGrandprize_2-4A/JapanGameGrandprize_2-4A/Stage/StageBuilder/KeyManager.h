#pragma once

class KeyManager
{
private:

	static char oldKey[256];
	static char nowKey[256];
	static int oldMouse;
	static int nowMouse;
	KeyManager() = default;
public:

	static void Update();

	static  bool OnKeyClicked(int Key);
	static  bool OnKeyReleased(int Key);
	static  bool OnKeyPressed(int Key);

	static  bool OnMouseClicked(int Key);
	static  bool OnMouseReleased(int Key);
	static  bool OnMousePressed(int Key);
};

/*

KEY_INPUT_BACK	// バックスペースキー
KEY_INPUT_TAB	// タブキー
KEY_INPUT_RETURN	// エンターキー

KEY_INPUT_LSHIFT	// 左シフトキー
KEY_INPUT_RSHIFT	// 右シフトキー
KEY_INPUT_LCONTROL	// 左コントロールキー
KEY_INPUT_RCONTROL	// 右コントロールキー
KEY_INPUT_ESCAPE	// エスケープキー
KEY_INPUT_SPACE	// スペースキー
KEY_INPUT_PGUP	// ＰａｇｅＵＰキー
KEY_INPUT_PGDN	// ＰａｇｅＤｏｗｎキー
KEY_INPUT_END	// エンドキー
KEY_INPUT_HOME	// ホームキー
KEY_INPUT_LEFT	// 左キー
KEY_INPUT_UP	// 上キー
KEY_INPUT_RIGHT	// 右キー
KEY_INPUT_DOWN	// 下キー
KEY_INPUT_INSERT	// インサートキー
KEY_INPUT_DELETE	// デリートキー

KEY_INPUT_MINUS	// －キー
KEY_INPUT_YEN	// ￥キー
KEY_INPUT_PREVTRACK	// ＾キー
KEY_INPUT_PERIOD	// ．キー
KEY_INPUT_SLASH	// ／キー
KEY_INPUT_LALT	// 左ＡＬＴキー
KEY_INPUT_RALT	// 右ＡＬＴキー
KEY_INPUT_SCROLL	// ScrollLockキー
KEY_INPUT_SEMICOLON	// ；キー
KEY_INPUT_COLON	// ：キー
KEY_INPUT_LBRACKET	// ［キー
KEY_INPUT_RBRACKET	// ］キー
KEY_INPUT_AT	// ＠キー
KEY_INPUT_BACKSLASH	// ＼キー
KEY_INPUT_COMMA	// ，キー
KEY_INPUT_CAPSLOCK	// CaspLockキー
KEY_INPUT_PAUSE	// PauseBreakキー

KEY_INPUT_NUMPAD0	// テンキー０
KEY_INPUT_NUMPAD1	// テンキー１
KEY_INPUT_NUMPAD2	// テンキー２
KEY_INPUT_NUMPAD3	// テンキー３
KEY_INPUT_NUMPAD4	// テンキー４
KEY_INPUT_NUMPAD5	// テンキー５
KEY_INPUT_NUMPAD6	// テンキー６
KEY_INPUT_NUMPAD7	// テンキー７
KEY_INPUT_NUMPAD8	// テンキー８
KEY_INPUT_NUMPAD9	// テンキー９
KEY_INPUT_MULTIPLY	// テンキー＊キー
KEY_INPUT_ADD	// テンキー＋キー
KEY_INPUT_SUBTRACT	// テンキー－キー
KEY_INPUT_DECIMAL	// テンキー．キー
KEY_INPUT_DIVIDE	// テンキー／キー
KEY_INPUT_NUMPADENTER	//*/