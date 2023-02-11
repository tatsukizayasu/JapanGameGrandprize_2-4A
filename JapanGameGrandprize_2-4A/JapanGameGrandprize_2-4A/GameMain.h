#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Stage/Stage.h"
#include "CameraWork.h"


class GameMain :
    public AbstractScene
{
private:

    //各クラスのオブジェクト
    Player* player;
    Stage* stage;
    CameraWork* camera_work;
    EnemyBase* enemy; //敵

    //操作間隔時間
    int input_margin;

public:
    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //更新
    AbstractScene* Update() override;

    //描画
    void Draw() const override;
};