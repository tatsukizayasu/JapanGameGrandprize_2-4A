#pragma once
#include "AbstractScene.h"

class GameOver :
	public AbstractScene
{
private:
    // フォントハンドル
    int menu_font;

    enum class MENU
    {
        RETRY,
        TITLE,
        MENU_SIZE
    };

    const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
        "RETRY",
        "TITLE"
    };

    // 選択しているメニュー
    int select_menu;

    //操作間隔時間
    int input_margin;

    //フェード用カウンタ
    int fade_counter;

    //プレイヤー所持元素
    unsigned int old_element_volume[7];

public:
    //コンストラクタ
    GameOver(short stage_num, unsigned int old_element_volume[7]);

    //デストラクタ
    ~GameOver();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;
};

