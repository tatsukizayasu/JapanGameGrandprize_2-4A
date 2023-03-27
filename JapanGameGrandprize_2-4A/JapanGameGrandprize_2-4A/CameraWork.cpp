#include "CameraWork.h"
#include "PadInput.h"

Location CameraWork::camera;

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
	player_dir_y = false;
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
	player_dir_y = false;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
CameraWork::~CameraWork()
{
	
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

	//カメラの状態が移動の場合のみ、X方向にカメラ移動する。
	if (state == STATE::MOVE) 
	{

		//移動開始ラインの変動

		float player_speed_w = player_p.x - old_player.x;
		if (player_dir == true)
		{
			if (moveing_line > 400) { moveing_line -= player_speed_w; }
		}
		else 
		{
			if (moveing_line < 800) { moveing_line -= player_speed_w; }
		}

		//マップの右端に着いたら止める
		if (static_cast<float>(stage->GetMapSize().x * CHIP_SIZE - (SCREEN_WIDTH - moveing_line)) 
			                                                        < ceilf(player->GetLocation().x))
		{
			state = STATE::FIXED;
			return;
		}

		//float player_speed = player_p.x - old_player.x;
		float player_speed = 1.0f;
		//printfDx("player_speed:%f\n", player_speed);

		if ((old_player.x != player_p.x) || (old_player.y != player_p.y)) 
		{
			// カメラの座標を更新
			camera.x = (player->GetLocation().x - moveing_line + player_speed) * speed;
			//camera.y = player->GetLocation().y - 700;

			// カメラの範囲がマップ外に出ないように調整
			if (camera.x < 0)
			{
				state = STATE::FIXED;
				camera.x = 0;
			}
			/*else if (camera.x > stage->GetMapSize().x * CHIP_SIZE - moveing_line) {
				camera.x = stage->GetMapSize().x * CHIP_SIZE - moveing_line;
			}*/
			if (camera.y < 0) 
			{
				//camera.y = 0;
			}
			else if (camera.y > stage->GetMapSize().y * CHIP_SIZE - 700) 
			{
				//camera.y = stage->GetMapSize().y * CHIP_SIZE - 700;
			}
		}

		{	//プレイヤーの向き
			float player_speed = player_p.x - old_player.x;
			if (player_speed < 0) 
			{
				player_dir = false;
			}
			else if (player_speed > 0) 
			{
				player_dir = true;
			}
		}
	}

	// カメラのy座標を更新
	if (player->GetLocation().y - camera.y < 200) 
	{
		camera.y = player->GetLocation().y - 200;
	}
	else if (player->GetLocation().y - camera.y > 420) 
	{
		camera.y = player->GetLocation().y - 420;
		//camera.y + 0.25;
	}

	if (camera.x < 0)
	{
		state = STATE::FIXED;
		camera.x = 0;
	}
	else if (camera.x > stage->GetMapSize().x * CHIP_SIZE - moveing_line) 
	{
		camera.x = stage->GetMapSize().x * CHIP_SIZE - moveing_line;
	}

	// カメラの範囲がマップ外に出ないように調整
	//マップ外
	if (camera.y < 0) 
	{
		camera.y = 0;
	}
	else if (camera.y > stage->GetMapSize().y * CHIP_SIZE - SCREEN_HEIGHT)
	{
		camera.y = stage->GetMapSize().y * CHIP_SIZE - SCREEN_HEIGHT;
	}

	float player_speed_y = player_p.y - old_player.y;

	if (player_speed_y < 0) 
	{
		player_dir_y = false;
	}
	else if (player_speed_y > 0) 
	{
		player_dir_y = true;
	}

	old_player.x = player_p.x;
	old_player.y = player_p.y;

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