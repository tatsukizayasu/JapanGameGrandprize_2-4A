#pragma once
#include "Player.h"
#include "Stage/Stage.h"

class CameraWork
{

protected:

	//カメラ座標
	//static POINT camera;

	//カメラ座標構造体
	struct Camera
	{
		float x;
		float y;
	};

	//プレイヤーの旧座標
	Camera old_player;
	//プレイヤーの向き
	//FALSE: 左		TRUE:右
	bool player_dir;

	//カメラスピード
	float speed;

	//カウント
	float count;


	//移動開始X座標
	float moveing_line;

	//オブジェクト
	static Camera camera;
	Player* player;
	Stage* stage;

	//入力間隔時間		デバック
	int input_margin;

public:
	enum class STATE {
		MOVE,	//移動
		FIXED	//固定
	};


	CameraWork();
	CameraWork(float camera_x, float camera_y, Player* player, Stage* stage);

	~CameraWork();
	void Update();
	static Camera GetCamera() { return camera; }



private:

	//カメラの状態
	STATE state;
};
