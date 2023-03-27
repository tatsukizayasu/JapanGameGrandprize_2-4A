#pragma once

class Pause {
private:

	bool is_paused;

	int title_font;

	int menu_font;

	int pause_graph;

	//カーソル位置
	short cursor_osition;

	
	short next_menu;

	int pause_effect_timer;
public:

	Pause();
	~Pause();

	void Update();
	void Draw() const;

	int GetDrawCenterX(const char* string, int font_handle)const;

	bool IsPause() { return is_paused; }

	short GetNextMenu() { return next_menu; }
};