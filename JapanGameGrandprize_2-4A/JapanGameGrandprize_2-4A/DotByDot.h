#pragma once
#include "AbstractScene.h"
#include "Define.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Stage/Stage.h"

class DotByDot :
    public AbstractScene
{
private:

    int state;
    EnemyBase** enemy;
    Player* player;
    Stage* stage;

    const char str[5][10] = { "idol","move","fall","attack","death" };
public:
    //コンストラクタ
    DotByDot();

    //デストラクタ
    ~DotByDot();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;
};

