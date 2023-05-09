#pragma once
#include "AbstractScene.h"
#include "../Player.h"
#include "../EnemyBase.h"
#include "../Stage/Stage.h"
#include "../CameraWork.h"
#include "../ItemController.h"
#include "../BulletManager.h"
#include "Pause.h"

class GameMain :
    public AbstractScene
{
private:

    int enemy_spawn_volume; //エネミーの数
    //各クラスのオブジェクト
    Pause* pause;
    Player* player;
    Stage* stage;
    CameraWork* camera_work;
    EnemyBase** enemy; //敵

    //ボスがスポーンしたかのフラグ
    bool is_spawn_boss;

    //背景画像座標
    Location background_location;


    //操作間隔時間
    int input_margin;
    int background_image[2];

    ItemController* item_controller; //アイテム管理
    BulletManager* bullet_manager; //弾の管理
public:


    GameMain() = default;
    //コンストラクタ
    GameMain(short stage_num);

    //デストラクタ
    ~GameMain();

    //更新
    AbstractScene* Update() override;

    //エネミーの生成
    void SpawnEnemy();

    //エネミーの更新処理
    bool EnemyUpdate();

    //描画
    void Draw() const override;
};