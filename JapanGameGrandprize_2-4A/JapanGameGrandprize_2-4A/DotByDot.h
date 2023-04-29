#pragma once
#include "AbstractScene.h"
#include "Define.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Stage/Element/Stage_Element.h"


class DotByDot :
    public AbstractScene
{
private:
    int font;
    int state;
    EnemyBase** enemy;
    Player* player;
    Stage_Element* element;



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

