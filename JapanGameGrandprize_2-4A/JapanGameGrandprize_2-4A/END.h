#pragma once
#include "AbstractScene.h"
#include <string>

class END :
    public AbstractScene
{
private:

    struct TOP_MENU
    {
        short number;
        std::string string;
    }top_menu[2];

    int select_menu;


    int menu_font;


    //選択SE用サウンドハンドル
    int select_se;
    //決定SE用サウンドハンドル
    int decision_se;
    
    //操作間隔時間
    int input_margin;
public:

    //コンストラクタ
    END();

    //デストラクタ
    ~END();

    //描画以外の更新を実行
    AbstractScene* Update() override;
   
    //描画に関することを実装
    void Draw() const override;
};