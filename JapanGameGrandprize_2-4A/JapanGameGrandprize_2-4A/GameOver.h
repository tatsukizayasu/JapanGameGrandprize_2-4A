#pragma once
#include "AbstractScene.h"
class GameOver :
	public AbstractScene
{
private:

public:
    //コンストラクタ
    GameOver(short stage_num);

    //デストラクタ
    ~GameOver();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;
};

