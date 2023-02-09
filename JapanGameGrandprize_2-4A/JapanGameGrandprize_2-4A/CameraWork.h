#pragma once
class CameraWork
{
private:

protected:

	//カメラ座標
	float camera_x;
	float camera_y;

	//入力間隔時間		デバック
	int input_margin;

	//スクロール速度	デバック
	int scroll_speed;	

public:

	CameraWork();
	CameraWork(float camera_x, float camera_y);

	~CameraWork();
	void Update();
};

