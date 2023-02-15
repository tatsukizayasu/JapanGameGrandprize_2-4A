#pragma once
#include "Player.h"
#include "Stage/Stage.h"

class CameraWork
{
private:



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

	//カメラスピード
	float speed;

	//カウント
	float count;

	//オブジェクト
	static Camera camera;
	Player* player;
	Stage* stage;

	//入力間隔時間		デバック
	int input_margin;

	//スクロール速度	デバック
	float scroll_speed;

public:

	CameraWork();
	CameraWork(float camera_x, float camera_y, Player* player, Stage* stage);

	~CameraWork();
	void Update();
	static Camera GetCamera() { return camera; }
};