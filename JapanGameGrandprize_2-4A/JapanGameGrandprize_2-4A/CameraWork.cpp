#include "CameraWork.h"
#include "PadInput.h"

CameraWork::Camera CameraWork::camera;

//#define DEBUG

//-----------------------------------
// コンストラクタ
//-----------------------------------
CameraWork::CameraWork()
{
	camera.x = 0.0f;
	camera.y = 0.0f;

	input_margin = 0;
	
	speed = 0;

	count = 0;

	old_player = { 0,0 };

	player = nullptr;
	this->stage = nullptr;

	//カメラの状態を固定に変更
	state = STATE::FIXED;

	moveing_line = 400.0f;

	player_dir = true;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
CameraWork::CameraWork(float camera_x, float camera_y, Player* player, Stage* stage)
{
	this->camera.x = camera_x;
	this->camera.y = camera_y;

	input_margin = 0;
	
	speed = 1.0f;

	count = 0;

	old_player = { 0,0 };

	this->player = player;
	this->stage = stage;

	//カメラの状態を固定に変更
	state = STATE::FIXED;

	moveing_line = 400.0f;

	player_dir = true;


}

//-----------------------------------
// デストラクタ
//-----------------------------------
CameraWork::~CameraWork()
{
	delete player;
}

//-----------------------------------
// 更新
//-----------------------------------
void CameraWork::Update()
{
	//printfDx("state:%d\n", state);

	//clsDx();
	Camera player_p;
	player_p = { player->GetLocation().x, player->GetLocation().y };
	//float player_x = player->GetLocation().x;

	//プレイヤーが移動開始ラインを超えたらカメラの状態を移動にする
	if (player_p.x > moveing_line) { state = STATE::MOVE; }


	//移動開始ラインの変動
	if (player_dir == true) {
		moveing_line = 400.0f;
	}
	else {
		moveing_line = 800.0f;
	}

	printfDx("player_dir:%d\n", player_dir);


	//カメラの状態が移動の場合
	if (state == STATE::MOVE) {

		

		//マップの右端に着いたら止める
		if (static_cast<float>(stage->GetMapSize().x * CHIP_SIZE - (SCREEN_WIDTH - moveing_line)) < ceilf(player->GetLocation().x)) {
			state = STATE::FIXED;
			return;
		}

		//float player_speed = player_p.x - old_player.x;
		float player_speed = 1.0f;
		//printfDx("player_speed:%f\n", player_speed);

		if ((old_player.x != player_p.x) || (old_player.y != player_p.y)) {
			// カメラの座標を更新
			camera.x = (player->GetLocation().x - moveing_line + player_speed) * speed;
			camera.y = player->GetLocation().y - 700;



			// カメラの範囲がマップ外に出ないように調整
			if (camera.x < 0) {
				state = STATE::FIXED;
				camera.x = 0;
			}
			/*else if (camera.x > stage->GetMapSize().x * CHIP_SIZE - moveing_line) {
				camera.x = stage->GetMapSize().x * CHIP_SIZE - moveing_line;
			}*/
			if (camera.y < 0) {
				camera.y = 0;
			}
			else if (camera.y > stage->GetMapSize().y * CHIP_SIZE - 700) {
				camera.y = stage->GetMapSize().y * CHIP_SIZE - 700;
			}
		}


		{	//プレイヤーの向き
			float player_speed = player_p.x - old_player.x;
			if (player_speed < 0) {
				player_dir = false;
			}
			else if (player_speed > 0) {
				player_dir = true;
			}

		}


		old_player.x = player_p.x;
		old_player.y = player_p.y;
	}

#ifdef DEBUG

	if (input_margin < 10)
	{
		input_margin++;
	}
	else
	{

		//スクロールスピードダウン
		if (CheckHitKey(KEY_INPUT_M))
		{
			if (scroll_speed > 0) { scroll_speed -= 1.0f; }
		}

		//スクロールスピードアップ
		else if (CheckHitKey(KEY_INPUT_L))
		{
			scroll_speed += 1.0f;
		}
	}

	//スクロール移動
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		camera.y -= scroll_speed;
	}
	else if (CheckHitKey(KEY_INPUT_UP))
	{
		camera.y += scroll_speed;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		camera.x += scroll_speed;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		camera.x -= scroll_speed;
	}
	input_margin = 0;

#endif // DEBUG



}