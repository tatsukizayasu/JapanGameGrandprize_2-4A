#pragma once
#include "AbstractScene.h"

// タイトルにデバックメニューを追加
#define TITLE_DEBUG

class Title :
    public AbstractScene
{
private:

    enum class MENU
    {
        PLAY,
        /*OPTION,
        HELP,*/
        EXIT,
        MENU_SIZE
    };

    const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
        "PLAY",
        "EXIT"
    };

    // 選択しているメニュー
    int select_menu;


    int menu_font;

#ifdef TITLE_DEBUG
    // デバックメニュー選択用フラグ
    bool is_select_debug;
#endif // TITLE_DEBUG

    //選択SE用サウンドハンドル
    int select_se;
    //決定SE用サウンドハンドル
    int decision_se;
    
    //操作間隔時間
    int input_margin;
public:

    //コンストラクタ
    Title();

    //デストラクタ
    ~Title();

    //描画以外の更新を実行
    AbstractScene* Update() override;
   
    //描画に関することを実装
    void Draw() const override;
};