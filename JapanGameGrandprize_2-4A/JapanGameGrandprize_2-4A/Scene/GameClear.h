#pragma once
#include "AbstractScene.h"

class ElementItem;

class GameClear :
    public AbstractScene
{
private:
    // フォントハンドル
    int menu_font;

    //プレイヤーの所持元素
    unsigned int element_volume[7];

public:
    //コンストラクタ
    GameClear(short stage_num, unsigned int element_volume[7]);

    //デストラクタ
    ~GameClear();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;

};

