#pragma once

class CameraWork
{
private:

protected:

	//カメラ座標
	//static POINT camera;

	struct Camera
	{
		float x;
		float y;
	};

	static Camera camera;

	/*static float camera_x;
	static float camera_y;*/

	//入力間隔時間		デバック
	int input_margin;

	//スクロール速度	デバック
	float scroll_speed;	

public:

	CameraWork();
	CameraWork(float camera_x, float camera_y);

	~CameraWork();
	void Update();
	static Camera GetCamera() { return camera; }
};