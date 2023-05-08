#pragma once
#include "AbstractScene.h"
class GameClear :
    public AbstractScene
{
private:
    // フォントハンドル
    int menu_font;

public:
    //コンストラクタ
    GameClear(short stage_num);

    //デストラクタ
    ~GameClear();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;

};

