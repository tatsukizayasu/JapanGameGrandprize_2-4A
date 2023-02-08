#pragma once
#include "AbstractScene.h"



class Title :
    public AbstractScene
    
{
private:

    //タイトルメニュー
    enum class TITLE_MENU
    {
        PLAY,
        OPTION,
        HELP,
        END
    };

    //背景用グラフィックハンドル
    int background_image;

    //タイトル名用フォントハンドル
    int title_font;

    //BGM用サウンドハンドル
    int bgm;

    //選択SE用サウンドハンドル
    int select_se;
    //決定SE用サウンドハンドル
    int decision_se;
    

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

