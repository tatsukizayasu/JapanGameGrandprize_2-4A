#pragma once
#include "AbstractScene.h"
class GameClear :
    public AbstractScene
{
private:

public:
    //コンストラクタ
    GameClear();

    //デストラクタ
    ~GameClear();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;

};

