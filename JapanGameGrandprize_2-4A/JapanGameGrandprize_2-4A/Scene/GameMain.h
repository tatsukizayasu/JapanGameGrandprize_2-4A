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


    //操作間隔時間
    int input_margin;

    static bool is_help_mode;  //ヘルプ用
    int help_image[2]; //コントローラ/操作説明の画像

    ItemController* item_controller; //アイテム管理
    BulletManager* bullet_manager; //弾の管理

    //ステージ開始時のプレイヤー所持元素
    unsigned int old_element_volume[PLAYER_ELEMENT];
    //ステージ開始時のプレイヤー所持弾丸
    ChemicalFormulaParameter old_chemical_bullets[BULLET_KINDS];

public:

    GameMain() = default;
    //コンストラクタ
    GameMain(short stage_num, unsigned int element_volume[PLAYER_ELEMENT], Pouch* pouch);

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

    void SetHelpMode(bool is_help);
};