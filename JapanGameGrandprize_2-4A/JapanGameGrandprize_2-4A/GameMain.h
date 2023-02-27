#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Stage/Stage.h"
#include "CameraWork.h"
#include "ItemController.h"

class GameMain :
    public AbstractScene
{
private:

    //各クラスのオブジェクト
    Player* player;
    Stage* stage;
    CameraWork* camera_work;
    EnemyBase** enemy; //敵

    //操作間隔時間
    int input_margin;

    ItemController* item_controller; //アイテム管理
public:

    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //更新
    AbstractScene* Update() override;

    //エネミーの更新処理
    void EnemyUpdate();

    //描画
    void Draw() const override;
};