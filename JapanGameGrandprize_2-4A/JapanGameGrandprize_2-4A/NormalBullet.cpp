#include "NormalBullet.h"
#include "CameraWork.h"
#include "Define.h"
#include "player.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
NormalBullet::NormalBullet()
{
	Tick = 0;
	Explosion[0].image = LoadGraph("Images/Player/img01.png");
	location.x = 0.0;
	location.y = 0.0;
	radius = 4;
	efect_count = 0;
	scrool_x = 0.0;
	scrool_y = 0.0;
	delete_flg = false;
	efect_end = false;

	for (int i = 0; i < 4; i++)
	{
		dot_location_x[i] = 0;
		dot_location_y[i] = 0;
		speed_y[i] = 0;
	}

	speed_x = 0;
}

//-----------------------------------//
// コンストラクタ					 //
//-----------------------------------//
NormalBullet::NormalBullet(float player_x, float player_y,
	                         bool direction,ChemicalFormulaParameter* chemical)
{
	Tick = 0;
	delete_flg = false;
	scrool_x = CameraWork::GetCamera().x;
	scrool_y = CameraWork::GetCamera().y;
	radius = 10.0f;

	location.x = player_x;
	location.y = player_y - 5;
	chemical_formula = chemical;
	damage = chemical->damage;
	debuff_time = chemical->time;
	attribute = chemical->atribute;
	this->player_state = player_state;
	player_direction = direction;

	switch (attribute)
	{
	case ATTRIBUTE::NORMAL:
		break;
	case ATTRIBUTE::EXPLOSION:
		Explosion[0].image = LoadGraph("Images/Player/img01.png");
		Explosion[1].x = player_x;
		Explosion[1].y = player_y;
		Explosion[1].X_radius = 5;
		Explosion[1].Y_radius = 10;
		break;
	case ATTRIBUTE::MELT:
		break;
	case ATTRIBUTE::PARALYSIS:
		break;
	case ATTRIBUTE::POISON:
		break;
	}

	efect_count = 0;
	delete_flg = false;
	efect_end = false;

	for (int i = 0; i < 4; i++)
	{
		dot_location_x[i] = 0;
		dot_location_y[i] = 0;
	}

	speed_x = 1;
	speed_y[0] = 10;
	speed_y[1] = 8;
	speed_y[2] = 6;
	speed_y[3] = 4;
}

//-----------------------------------
// 描画
//-----------------------------------
void NormalBullet::Draw() const
{

	float scrool_x = CameraWork::GetCamera().x;
	float scrool_y = CameraWork::GetCamera().y;

	switch (attribute)
	{
	case ATTRIBUTE::NORMAL:
		if (delete_flg)
		{
			if (!efect_end)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					DrawCircle(dot_location_x[i] - scrool_x, dot_location_y[i] - scrool_y, 2, 0x000000, TRUE);
				}
			}
		}
		else
		{
			DrawBox(location.x - scrool_x, location.y - scrool_y, (location.x - scrool_x) + 20, (location.y - scrool_y) + 10, GLAY, TRUE);
		}
		break;
	case ATTRIBUTE::EXPLOSION:
		if (delete_flg)
		{
			if (!efect_end)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					DrawCircle(dot_location_x[i] - scrool_x, dot_location_y[i] - scrool_y, 2, 0x000000, TRUE);
				}
			}
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			for (int i = 0; i < 5; i++) 
			{
				DrawRotaGraph(location.x - scrool_x, location.y - scrool_y, 1, 1, Explosion[0].image, TRUE, FALSE);
			}
			if (Explosion[1].display_permit == TRUE && Explosion[1].BrendMode_ALPFA > 0) 
			{
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, Explosion[1].BrendMode_ALPFA);
				DrawOvalAA(Explosion[1].x, Explosion[1].y, Explosion[1].X_radius - 10, Explosion[1].Y_radius - 10, 20, 0xff0000, FALSE, 10);
				DrawOvalAA(Explosion[1].x, Explosion[1].y, Explosion[1].X_radius, Explosion[1].Y_radius, 20, 0xff0000, FALSE, 6);
			}
			for (int i = 0; i < PARTICLE; i++) 
			{
				if (Explosion[2].display_permit_Array[i] == TRUE) 
				{
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					SetDrawBlendMode(DX_BLENDMODE_ADD, Explosion[2].BrendMode_ALPFA_Array[i]);
					DrawOvalAA(Explosion[2].x_Array[i] + 10, Explosion[2].y_Array[i], 8, Explosion[2].OvalY_Array_radius[i], 20, 0xff0000, FALSE, 3.0f);
				}
			}
			for (int i = 0; i < PARTICLE; i++) 
			{
				if (Explosion[3].display_permit_Array[i] == TRUE) 
				{
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, Explosion[3].BrendMode_ALPFA_Array[i]);
					DrawRotaGraph(Explosion[3].x_Array[i] - 10, Explosion[3].y_Array[i], 1.5, 1, Explosion[0].image, true, false);
				}
			}
			//DrawBox(location.x - scrool_x, location.y - scrool_y, (location.x - scrool_x) + 20, (location.y - scrool_y) + 10, ORANGE, TRUE);
		}
		break;
	case ATTRIBUTE::MELT:
		if (delete_flg)
		{
			if (!efect_end)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					DrawCircle(dot_location_x[i] - scrool_x, dot_location_y[i] - scrool_y, 2, 0x000000, TRUE);
				}
			}
		}
		else
		{
			DrawBox(location.x - scrool_x, location.y - scrool_y, (location.x - scrool_x) + 20, (location.y - scrool_y) + 10, BLUE, TRUE);
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		if (delete_flg)
		{
			if (!efect_end)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					DrawCircle(dot_location_x[i] - scrool_x, dot_location_y[i] - scrool_y, 2, 0x000000, TRUE);
				}
			}
		}
		else
		{
			DrawBox(location.x - scrool_x, location.y - scrool_y, (location.x - scrool_x) + 20, (location.y - scrool_y) + 10, YELLOW, TRUE);
		}
		break;
	case ATTRIBUTE::POISON:
		if (delete_flg)
		{
			if (!efect_end)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					DrawCircle(dot_location_x[i] - scrool_x, dot_location_y[i] - scrool_y, 2, 0x000000, TRUE);
				}
			}
		}
		else
		{
			DrawBox(location.x - scrool_x, location.y - scrool_y, (location.x - scrool_x) + 20, (location.y - scrool_y) + 10, PURPLE, TRUE);
		}
		break;
	default:
		break;
	}
}

//-----------------------------------
// 更新
//-----------------------------------
void NormalBullet::Update(const Stage* stage_pointa)
{
	Tick++;
	float scrool_x = CameraWork::GetCamera().x;
	if (!player_direction)
	{
		if (!HitBlock(stage_pointa) && location.x - scrool_x < 1280 && !delete_flg)//弾の座標更新(右
		{
			switch (attribute)
			{
			case ATTRIBUTE::NORMAL:
				location.x += BULLET_SPEED;
				break;
			case ATTRIBUTE::EXPLOSION:
				location.x += 5;
				if (Tick == 1) 
				{
					if (Explosion[1].display_permit == FALSE) 
					{
						Explosion[1].x = location.x;
						Explosion[1].y = location.y;
						Explosion[1].X_radius = 5;
						Explosion[1].Y_radius = 10;
						Explosion[1].display_permit = TRUE;
					}
				}
				break;
			case ATTRIBUTE::MELT:
				location.x += 2;
				break;
			case ATTRIBUTE::PARALYSIS:
				location.x += 2;
				break;
			case ATTRIBUTE::POISON:
				location.x += 2;
				break;
			}

			//location.x += BULLET_SPEED;

		}
		else                   //着弾時のエフェクトの座標更新(右
		{
			if (!delete_flg)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					dot_location_x[i] = location.x;
					dot_location_y[i] = location.y;
				}
			}
			delete_flg = true;
		}
	}

	if (player_direction)
	{
		if (!HitBlock(stage_pointa) && location.x - scrool_x > 0 && !delete_flg)//弾の座標更新(左
		{
			switch (attribute)
			{
			case ATTRIBUTE::NORMAL:
				location.x -= BULLET_SPEED;
				break;
			case ATTRIBUTE::EXPLOSION:
				location.x -= 5;
				break;
			case ATTRIBUTE::MELT:
				location.x -= 2;
				break;
			case ATTRIBUTE::PARALYSIS:
				location.x -= 2;
				break;
			case ATTRIBUTE::POISON:
				location.x -= 2;
				break;
			}

			//location.x -= BULLET_SPEED;
		
		}
		else                   //着弾時のエフェクトの座標更新(左
		{
			if (!delete_flg)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					dot_location_x[i] = location.x;
					dot_location_y[i] = location.y;
				}
			}
			delete_flg = true;
		}
	}

	if (delete_flg)
	{
		NormalBulletEfect();
	}
}

bool NormalBullet::NormalBulletEfect()		//着弾エフェクト
{

	if (!efect_end)
	{
		if (++efect_count % 30 != 0)
		{
			for (int i = 0; i < PIXEL_MAX; i++)
			{
				if (player_direction)
				{
					dot_location_x[i] += speed_x;
					dot_location_y[i] += speed_y[i];
				}
				else
				{
					dot_location_x[i] -= speed_x;
					dot_location_y[i] += speed_y[i];
				}
			}
		}
		else
		{
			if (player_direction)
			{
				location.x--;
				location.y--;
				efect_end = true;
				return true;
			}
			else
			{
				location.x++;
				location.y++;
				efect_end = true;
				return true;
			}
		}
	}
	return false;
}