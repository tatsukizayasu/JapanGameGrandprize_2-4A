#pragma once
#include "AbstractScene.h"

class Pouch;

class GameClear :
    public AbstractScene
{
private:
    // フォントハンドル
    int menu_font;

    //プレイヤーの所持元素
    unsigned int element_volume[7];

    Pouch* pouch;

public:
    //コンストラクタ
    GameClear(short stage_num, unsigned int element_volume[7], Pouch* pouch);

    //デストラクタ
    ~GameClear();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;

};

