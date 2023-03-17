#pragma once

class Pause {
private:
	bool is_paused;

	int title_font;

	int pause_graph;
	int pause_effect_timer;

public:
	Pause();
	~Pause();

	void Update();
	void Draw();

	int GetDrawCenterX(const char* string, int font_handle)const;

	bool IsPause() { return is_paused; }
};

