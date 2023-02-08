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

