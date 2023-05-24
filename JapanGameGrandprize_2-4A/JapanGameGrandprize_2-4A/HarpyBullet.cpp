#include "HarpyBullet.h"
#include "CameraWork.h"

//ハーピィの遠距離攻撃の移動速度
#define HARPY_BULLET_SPEED 8

//ハーピィの遠距離ダメージ
#define HARPY_BULLET_DAMAGE 5

//-----------------------------------
//コンストラクタ
//-----------------------------------
HarpyBullet::HarpyBullet(const Location spawn_location, const Location player_location)
{

	Tick = 0;
	frame = 0;
	angle = 0;
	PHASE = 0;
	type = ENEMY_TYPE::WIND;
	location = spawn_location;
	radius = 5;
	speed = HARPY_BULLET_SPEED;
	LoadDivGraph("images/Enemy/Harpy/Harpy2.png", 20, 5, 4, 192, 192, image);
	damage = HARPY_BULLET_DAMAGE;
	display_permit = FALSE;
	float radian; //角度
	radian = atan2f(player_location.y - location.y, player_location.x - location.x);
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));
}

//-----------------------------------
//デストラクタ
//-----------------------------------
HarpyBullet::~HarpyBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void HarpyBullet::Update()
{
	Tick++;

	location.x += x_speed;
	location.y += y_speed;

	switch (PHASE) {
	case 0:
		if (Tick == 1) {
			frame = 0;
			display_permit = TRUE;
		}
		if (Tick % 2 == 0) {
			//HIT
			frame++;
			if (frame > 19)
			{
				//ハーピィエフェクト切り替え場所

				/*display_permit = FALSE;
				PHASE++;
				Tick = 0;*/
			}
			else //壁に当たるまでループ
			{
				frame++;
				if (frame > 14) {
					frame = 5;
				}
			}
		}
		break;
	case 1:
		/*if (Tick == 1) {
			TS[1].Extend_rate = 1;
			TS[1].frame = 0;
			TS[1].display_permit = TRUE;
			TS[1].BrendMode_ALPFA = 255;
		}
		if (Tick % 2 == 0) {
			TS[1].frame++;
			if (TS[1].frame > 19) {
				Tick = 0;
				ShotFlag[i] = 0;
			}
		}
		break;*/
	default:
		break;
	}


}

//-----------------------------------
//描画のみ
//-----------------------------------
void HarpyBullet::Draw() const
{

	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	DrawCircle(x, y, radius, 0xffffff, TRUE);
	if (display_permit == TRUE) 
	{
		DrawRotaGraph(x, y, 0.4, angle, image[frame], TRUE, FALSE, FALSE);
	}

	/*if (TS[1].display_permit == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, TS[1].BrendMode_ALPFA);
		DrawRotaGraph(TS[1].Pos_x, TS[1].Pos_y, TS[1].Extend_rate, 0, TS[1].image_Array[TS[1].frame], TRUE, FALSE, FALSE);
	}*/
}


