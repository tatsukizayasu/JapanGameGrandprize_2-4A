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

    /// <summary>
    /// 文字の描画するX座標が中心になるX座標を取得する。
    /// </summary>
    /// <param name="string">描画する文字列</param>
    /// <param name="font_handle">描画に使用するフォントハンドル(未入力又は0の場合はデフォルトフォントハンドルを使用</param>
    /// <param name="margin">中央のX座標に間隔を空ける値</param>
    int GetDrawCenterX(const char* string, int font_handle = 0, int margin = 0) const;
};