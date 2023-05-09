#pragma once
#include <string>

class Pause {
public:
	enum class MENU
	{
		RETURN,
		RETRY,
		TITLE,
		MENU_SIZE
	};

private:

	bool is_paused;

	int title_font;

	int menu_font;

	int enter_se;
	int cursor_move_se;

	int pause_graph;

	//カーソル位置
	short cursor_osition;

	
	short next_scene;


	const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
		"RETURN",
		"RETRY",
		"TITLE"
	};

	// 選択しているメニュー
	int select_menu;

	//操作間隔時間
	int input_margin;

	int pause_effect_timer;


public:

	Pause();
	~Pause();

	void Update(short stage_num);
	void Draw() const;

	//ポーズの切り替え
	void TogglePause();

	int GetDrawCenterX(const char* string, int font_handle)const;

	bool IsPause() { return is_paused; }

	short GetNextScene() { return next_scene; }
};