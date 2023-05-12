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
	Melt[0].image = LoadGraph("Images/Player/img02.png");
	Poison[0].image = LoadGraph("Images/Player/img03.png");
	Paralysis[0].image = LoadGraph("Images/Player/img04.png");
	LoadDivGraph("Images/Player/着弾エフェクト_exp_2.png", 8, 8, 1, 120, 120, exp.Delete_image_array, TRUE, FALSE, FALSE);
	LoadDivGraph("Images/Player/着弾エフェクト_mel_2.png", 8, 8, 1, 120, 120, mel.Delete_image_array, TRUE, FALSE, FALSE);
	LoadDivGraph("Images/Player/着弾エフェクト_poi_2.png", 8, 8, 1, 120, 120, poi.Delete_image_array, TRUE, FALSE, FALSE);
	LoadDivGraph("Images/Player/着弾エフェクト_par_2.png", 8, 8, 1, 120, 120, par.Delete_image_array, TRUE, FALSE, FALSE);
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
		Explosion[1].X_radius = 3;
		Explosion[1].Y_radius = 5;
		LoadDivGraph("Images/Player/着弾エフェクト_exp_2.png", 8, 8, 1, 120, 120, exp.Delete_image_array, TRUE, FALSE, FALSE);
		exp.Delete_display_permit = FALSE;
		exp.Delete_frame = 0;
		for (int i = 0; i < PARTICLE; i++) 
		{
			Explosion[3].display_permit_Array[i] = FALSE;
			Explosion[2].display_permit_Array[i] = FALSE;
			Explosion[3].BrendMode_ALPFA_Array[i] = 255;
			Explosion[2].BrendMode_ALPFA_Array[i] = 255;
			Explosion[1].BrendMode_ALPFA = 255;
			Explosion[2].OvalY_Array_radius[i] = 7.5f;
			Explosion[2].OvalY_Array_permit[i] = FALSE;
		}

		break;
	case ATTRIBUTE::MELT:
		LoadDivGraph("Images/Player/着弾エフェクト_mel_2.png", 8, 8, 1, 120, 120, mel.Delete_image_array, TRUE, FALSE, FALSE);
		Melt[0].image = LoadGraph("Images/Player/img02.png");
		for (int i = 0; i < PARTICLE; i++)
		{
			Melt[1].display_permit_Array[i] = FALSE;
			Melt[1].BrendMode_ALPFA_Array[i] = 255;
		}
		break;
	case ATTRIBUTE::POISON:
		LoadDivGraph("Images/Player/着弾エフェクト_poi_2.png", 8, 8, 1, 120, 120, poi.Delete_image_array, TRUE, FALSE, FALSE);
		Poison[0].image = LoadGraph("Images/Player/img03.png");
		for (int i = 0; i < PARTICLE; i++)
		{
			Poison[1].display_permit_Array[i] = FALSE;
			Poison[1].BrendMode_ALPFA_Array[i] = 255;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		LoadDivGraph("Images/Player/着弾エフェクト_par_2.png", 8, 8, 1, 120, 120, par.Delete_image_array, TRUE, FALSE, FALSE);
		Paralysis[0].image = LoadGraph("Images/Player/img04.png");
		for (int i = 0; i < PARTICLE; i++) 
		{
			Paralysis[1].display_permit_Array[i] = FALSE;
			Paralysis[1].BrendMode_ALPFA_Array[i] = 255;
		}
		break;
	default:
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
			DrawCircle(location.x - scrool_x, location.y - scrool_y, radius, GLAY, TRUE);
		}
		break;
	case ATTRIBUTE::EXPLOSION:
		if (delete_flg ==TRUE)
		{
			if (!efect_end)
			{
				for (int i = 0; i < PIXEL_MAX; i++)
				{
					
				}
			}
		}
		else
		{
			if (exp.Delete_display_permit == FALSE) 
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
					DrawOvalAA(Explosion[1].x - scrool_x, Explosion[1].y - scrool_y, Explosion[1].X_radius - 10, Explosion[1].Y_radius - 10, 20, 0xff0000, FALSE, 10);
					DrawOvalAA(Explosion[1].x - scrool_x, Explosion[1].y - scrool_y, Explosion[1].X_radius, Explosion[1].Y_radius, 20, 0xff0000, FALSE, 6);
				}
				for (int i = 0; i < PARTICLE; i++)
				{
					if (Explosion[2].display_permit_Array[i] == TRUE)
					{
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						SetDrawBlendMode(DX_BLENDMODE_ADD, Explosion[2].BrendMode_ALPFA_Array[i]);
						DrawOvalAA(Explosion[2].x_Array[i] - scrool_x, Explosion[2].y_Array[i] - scrool_y, 8, Explosion[2].OvalY_Array_radius[i], 20, 0xff0000, FALSE, 3.0f);
					}
				}
				for (int i = 0; i < PARTICLE; i++)
				{
					if (Explosion[3].display_permit_Array[i] == TRUE)
					{
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, Explosion[3].BrendMode_ALPFA_Array[i]);
						DrawRotaGraph(Explosion[3].x_Array[i] - scrool_x, Explosion[3].y_Array[i] - scrool_y, 1.5, 1, Explosion[0].image, TRUE, FALSE);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else 
			{
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				DrawRotaGraph(exp.Delete_x - scrool_x, exp.Delete_y - scrool_y, 1, 0, exp.Delete_image_array[exp.Delete_frame], TRUE, FALSE, FALSE);
			}
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
			if (mel.Delete_display_permit == FALSE) 
			{
				for (int i = 0; i < PARTICLE; i++)
				{
					if (Melt[1].display_permit_Array[i] == TRUE)
					{
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, Melt[1].BrendMode_ALPFA_Array[i]);
						DrawRotaGraph(Melt[1].x_Array[i] - scrool_x, Melt[1].y_Array[i] - scrool_y, 2.0, 1, Melt[0].image, TRUE, FALSE);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				for (int j = 0; j < 2; j++)
				{
					DrawRotaGraph(location.x - scrool_x, location.y - scrool_y, 1, 1, Melt[0].image, TRUE, FALSE);
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else 
			{
				DrawRotaGraph(mel.Delete_x - scrool_x, mel.Delete_y - scrool_y, 1, 0, mel.Delete_image_array[mel.Delete_frame], TRUE, FALSE, FALSE);
			}
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
			if (poi.Delete_display_permit == FALSE) 
			{
				for (int i = 0; i < PARTICLE; i++)
				{
					if (Poison[1].display_permit_Array[i] == TRUE)
					{
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, Poison[1].BrendMode_ALPFA_Array[i]);
						DrawRotaGraph(Poison[1].x_Array[i] - scrool_x, Poison[1].y_Array[i] - scrool_y, 2.0, 1, Poison[0].image, TRUE, FALSE);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				for (int j = 0; j < 2; j++)
				{
					DrawRotaGraph(location.x - scrool_x, location.y - scrool_y, 1, 1, Poison[0].image, TRUE, FALSE);
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				DrawRotaGraph(poi.Delete_x - scrool_x, poi.Delete_y - scrool_y, 1, 0, poi.Delete_image_array[poi.Delete_frame], TRUE, FALSE, FALSE);
			}	
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
			if (par.Delete_display_permit == FALSE) 
			{
				for (int i = 0; i < PARTICLE; i++)
				{
					if (Paralysis[1].display_permit_Array[i] == TRUE)
					{
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, Paralysis[1].BrendMode_ALPFA_Array[i]);
						DrawRotaGraph(Paralysis[1].x_Array[i] - scrool_x, Paralysis[1].y_Array[i] - scrool_y, 2.0, 1, Paralysis[0].image, TRUE, FALSE);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				for (int j = 0; j < 2; j++)
				{
					DrawRotaGraph(location.x - scrool_x, location.y - scrool_y, 1, 1, Paralysis[0].image, TRUE, FALSE);
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else 
			{
				DrawRotaGraph(par.Delete_x - scrool_x, par.Delete_y - scrool_y, 1, 0, par.Delete_image_array[par.Delete_frame], TRUE, FALSE, FALSE);
			}
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
	srand((unsigned)time(NULL));
	Tick++;
	float scrool_x = CameraWork::GetCamera().x;
	if (!player_direction)
	{
		if (!HitBlock(stage_pointa) && location.x - scrool_x < 1280 && !delete_flg)
		{
			switch (attribute)
			{
			case ATTRIBUTE::NORMAL:
				location.x += BULLET_SPEED;
				break;
			case ATTRIBUTE::EXPLOSION:
				if (GetDelete_flg() == FALSE) 
				{
					location.x += EXPLOSION_BULLET_SPEED;
					if (Tick == 1)
					{
						if (Explosion[1].display_permit == FALSE)
						{
							Explosion[1].x = location.x + 22;
							Explosion[1].y = location.y;
							Explosion[1].X_radius = 4.0;
							Explosion[1].Y_radius = 8.0;
							Explosion[1].display_permit = TRUE;
						}
					}
					if (Tick % 8 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Explosion[2].display_permit_Array[i] == 0)
							{
								Explosion[2].x_Array[i] = location.x + 10;
								Explosion[2].y_Array[i] = location.y;
								Explosion[2].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					if (Tick % 2 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Explosion[3].display_permit_Array[i] == 0)
							{
								Explosion[3].x_Array[i] = location.x - 10;
								Explosion[3].y_Array[i] = location.y + rand() % 8 - 3;
								Explosion[3].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					if (Explosion[1].display_permit == TRUE)
					{
						Explosion[1].X_radius = Explosion[1].X_radius * 1.11;
						Explosion[1].Y_radius = Explosion[1].Y_radius * 1.11;
						Explosion[1].BrendMode_ALPFA -= 10;
						if (Explosion[1].BrendMode_ALPFA <= 0)
						{
							Explosion[1].display_permit = FALSE;
							Explosion[1].BrendMode_ALPFA = 255;
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Explosion[2].display_permit_Array[i] == TRUE)
						{
							Explosion[2].BrendMode_ALPFA_Array[i] -= 6;
							if (Explosion[2].OvalY_Array_permit[i] == FALSE)
							{
								Explosion[2].OvalY_Array_radius[i] += 1.5 * 2.0;
							}
							else
							{
								Explosion[2].OvalY_Array_radius[i] -= 0.5 * 2.0;
							}

							if (Explosion[2].OvalY_Array_permit[i] == FALSE && Explosion[2].OvalY_Array_radius[i] > 15.0 * 2.0)
							{
								Explosion[2].OvalY_Array_permit[i] = TRUE;
							}
							if (Explosion[2].OvalY_Array_permit[i] == TRUE && Explosion[2].OvalY_Array_radius[i] < 0.0)
							{
								Explosion[2].display_permit_Array[i] = FALSE;
								Explosion[2].BrendMode_ALPFA_Array[i] = 255;
								Explosion[2].OvalY_Array_radius[i] = 7.5 * 2.0;
								Explosion[2].OvalY_Array_permit[i] = FALSE;
								continue;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Explosion[3].display_permit_Array[i] == TRUE)
						{
							Explosion[3].BrendMode_ALPFA_Array[i] -= 12;
							if (Explosion[3].BrendMode_ALPFA_Array[i] <= 0)
							{
								Explosion[3].display_permit_Array[i] = FALSE;
								Explosion[3].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else 
				{
					if (efect_end == FALSE) {
						if (Tick % 2 == 0)
						{
							exp.Delete_frame++;
						}
						if (exp.Delete_frame > 8)
						{
							exp.Delete_display_permit = FALSE;
							efect_end = TRUE;
						}
					}
				}
				break;
			case ATTRIBUTE::MELT:
				if (GetDelete_flg() == FALSE)
				{
					location.x += MELT_BULLET_SPEED;
					if (Tick % 2 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Melt[1].display_permit_Array[i] == FALSE)
							{
								Melt[1].x_Array[i] = location.x + 5;
								Melt[1].y_Array[i] = location.y + rand() % 8 - 3;
								Melt[1].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Melt[1].display_permit_Array[i] == TRUE)
						{
							Melt[1].BrendMode_ALPFA_Array[i] -= 12;
							if (Melt[1].BrendMode_ALPFA_Array[i] <= 0)
							{
								Melt[1].display_permit_Array[i] = FALSE;
								Melt[1].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else 
				{
					if (efect_end == false) {
						if (Tick % 3 == 0) {
							mel.Delete_frame++;
						}
						if (mel.Delete_frame > 8) {
							mel.Delete_display_permit = FALSE;
							mel.Delete_frame = 0;
							efect_end = TRUE;
							Tick = 0;
						}
					}
				}
				break;
			case ATTRIBUTE::POISON:
				if (GetDelete_flg() == FALSE)
				{
					location.x += POISON_BULLET_SPEED;
					if (Tick % 2 == 0) 
					{
						for (int i = 0; i < PARTICLE; i++) 
						{
							if (Poison[1].display_permit_Array[i] == FALSE) 
							{
								Poison[1].x_Array[i] = location.x + 5;
								Poison[1].y_Array[i] = location.y + rand() % 8 - 3;
								Poison[1].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++) 
					{
						if (Poison[1].display_permit_Array[i] == TRUE) 
						{
							Poison[1].BrendMode_ALPFA_Array[i] -= 12;
							if (Poison[1].BrendMode_ALPFA_Array[i] <= 0) 
							{
								Poison[1].display_permit_Array[i] = FALSE;
								Poison[1].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else 
				{
					if (efect_end == false) {
						if (Tick % 3 == 0) {
							poi.Delete_frame++;
						}
						if (poi.Delete_frame > 8) {
							poi.Delete_display_permit = FALSE;
							poi.Delete_frame = 0;
							efect_end = TRUE;
							Tick = 0;
						}
					}
				}
				break;
			case ATTRIBUTE::PARALYSIS:
				if (GetDelete_flg() == FALSE)
				{
					location.x += PARARYSIS_BULLET_SPEED;
					if (Tick % 2 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Paralysis[1].display_permit_Array[i] == FALSE)
							{
								Paralysis[1].x_Array[i] = location.x + 5;
								Paralysis[1].y_Array[i] = location.y + rand() % 8 - 3;
								Paralysis[1].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Paralysis[1].display_permit_Array[i] == TRUE)
						{
							Paralysis[1].BrendMode_ALPFA_Array[i] -= 12;
							if (Paralysis[1].BrendMode_ALPFA_Array[i] <= 0)
							{
								Paralysis[1].display_permit_Array[i] = FALSE;
								Paralysis[1].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else 
				{
					if (efect_end == false) {
						if (Tick % 3 == 0) {
							par.Delete_frame++;
						}
						if (par.Delete_frame > 8) {
							par.Delete_display_permit = FALSE;
							par.Delete_frame = 0;
							efect_end = TRUE;
							Tick = 0;
						}
					}
				}
				break;
			}
		}
		else
		{
			switch (attribute) 
			{
			case ATTRIBUTE::EXPLOSION:
				exp.Delete_x = location.x;
				exp.Delete_y = location.y;
				exp.Delete_display_permit = TRUE;
				break;
			case ATTRIBUTE::MELT:
				break;
			case ATTRIBUTE::PARALYSIS:
				break;
			case ATTRIBUTE::POISON:
				break;
			default:
				if (!delete_flg)
				{

					for (int i = 0; i < PIXEL_MAX; i++)
					{
						dot_location_x[i] = location.x;
						dot_location_y[i] = location.y;
					}
				}
				break;
			}
			delete_flg = true;
		}
	}

	if (player_direction)
	{
		if (!HitBlock(stage_pointa) && location.x - scrool_x > 0 && !delete_flg)
		{
			switch (attribute)
			{
			case ATTRIBUTE::NORMAL:
				location.x -= BULLET_SPEED;
				break;
			case ATTRIBUTE::EXPLOSION:
				if (GetDelete_flg() == FALSE) 
				{
					location.x -= EXPLOSION_BULLET_SPEED;
					if (Tick == 1)
					{
						if (Explosion[1].display_permit == FALSE)
						{
							Explosion[1].x = location.x - 22;
							Explosion[1].y = location.y;
							Explosion[1].X_radius = 4;
							Explosion[1].Y_radius = 8;
							Explosion[1].display_permit = TRUE;
						}
					}
					if (Tick % 8 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Explosion[2].display_permit_Array[i] == 0)
							{
								Explosion[2].x_Array[i] = location.x - 15;
								Explosion[2].y_Array[i] = location.y;
								Explosion[2].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					if (Tick % 2 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Explosion[3].display_permit_Array[i] == 0)
							{
								Explosion[3].x_Array[i] = location.x + 15;
								Explosion[3].y_Array[i] = location.y + rand() % 8 - 3;
								Explosion[3].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					if (Explosion[1].display_permit == TRUE)
					{
						Explosion[1].X_radius = Explosion[1].X_radius * 1.11;
						Explosion[1].Y_radius = Explosion[1].Y_radius * 1.11;
						Explosion[1].BrendMode_ALPFA -= 10;
						if (Explosion[1].BrendMode_ALPFA <= 0)
						{
							Explosion[1].display_permit = FALSE;
							Explosion[1].BrendMode_ALPFA = 255;
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Explosion[2].display_permit_Array[i] == TRUE)
						{
							Explosion[2].BrendMode_ALPFA_Array[i] -= 6;
							if (Explosion[2].OvalY_Array_permit[i] == FALSE)
							{
								Explosion[2].OvalY_Array_radius[i] += 1.5 * 2.0;
							}
							else
							{
								Explosion[2].OvalY_Array_radius[i] -= 0.5 * 2.0;
							}
							if (Explosion[2].OvalY_Array_permit[i] == FALSE && Explosion[2].OvalY_Array_radius[i] > 15.0 * 2.0)
							{
								Explosion[2].OvalY_Array_permit[i] = TRUE;
							}
							if (Explosion[2].OvalY_Array_permit[i] == TRUE && Explosion[2].OvalY_Array_radius[i] < 0.0)
							{
								Explosion[2].display_permit_Array[i] = FALSE;
								Explosion[2].BrendMode_ALPFA_Array[i] = 255;
								Explosion[2].OvalY_Array_radius[i] = 7.5 * 2.0;
								Explosion[2].OvalY_Array_permit[i] = FALSE;
								continue;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Explosion[3].display_permit_Array[i] == TRUE)
						{
							Explosion[3].BrendMode_ALPFA_Array[i] -= 12;
							if (Explosion[3].BrendMode_ALPFA_Array[i] <= 0)
							{
								Explosion[3].display_permit_Array[i] = FALSE;
								Explosion[3].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else 
				{
					if (efect_end == FALSE) {
						if (Tick % 2 == 0)
						{
							exp.Delete_frame++;
						}
						if (exp.Delete_frame > 8)
						{
							exp.Delete_display_permit = FALSE;
							efect_end = TRUE;
						}
					}
				}
				break;
			case ATTRIBUTE::MELT:
				if (GetDelete_flg() == FALSE) 
				{
					location.x -= MELT_BULLET_SPEED;
					if (Tick % 2 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Melt[1].display_permit_Array[i] == FALSE)
							{
								Melt[1].x_Array[i] = location.x - 5;
								Melt[1].y_Array[i] = location.y + rand() % 8 - 3;
								Melt[1].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Melt[1].display_permit_Array[i] == TRUE)
						{
							Melt[1].BrendMode_ALPFA_Array[i] -= 12;
							if (Melt[1].BrendMode_ALPFA_Array[i] <= 0)
							{
								Melt[1].display_permit_Array[i] = FALSE;
								Melt[1].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else 
				{
					if (Tick % 3 == 0) {
						mel.Delete_frame++;
					}
					if (mel.Delete_frame > 8) {
						mel.Delete_display_permit = FALSE;
						mel.Delete_frame = 0;
						Tick = 0;
					}
				}
				break;
			case ATTRIBUTE::POISON:
				if (GetDelete_flg() == FALSE) 
				{
					location.x -= POISON_BULLET_SPEED;
					if (Tick % 2 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Poison[1].display_permit_Array[i] == FALSE)
							{
								Poison[1].x_Array[i] = location.x - 5;
								Poison[1].y_Array[i] = location.y + rand() % 8 - 3;
								Poison[1].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Poison[1].display_permit_Array[i] == TRUE)
						{
							Poison[1].BrendMode_ALPFA_Array[i] -= 12;
							if (Poison[1].BrendMode_ALPFA_Array[i] <= 0)
							{
								Poison[1].display_permit_Array[i] = FALSE;
								Poison[1].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else {
					if (Tick % 3 == 0) {
						poi.Delete_frame++;
					}
					if (poi.Delete_frame > 8) {
						poi.Delete_display_permit = FALSE;
						poi.Delete_frame = 0;
						Tick = 0;
					}
				}
				break;
			case ATTRIBUTE::PARALYSIS:
				if (GetDelete_flg() == FALSE) 
				{
					location.x -= PARARYSIS_BULLET_SPEED;
					if (Tick % 2 == 0)
					{
						for (int i = 0; i < PARTICLE; i++)
						{
							if (Paralysis[1].display_permit_Array[i] == FALSE)
							{
								Paralysis[1].x_Array[i] = location.x - 5;
								Paralysis[1].y_Array[i] = location.y + rand() % 8 - 3;
								Paralysis[1].display_permit_Array[i] = TRUE;
								break;
							}
						}
					}
					for (int i = 0; i < PARTICLE; i++)
					{
						if (Paralysis[1].display_permit_Array[i] == TRUE)
						{
							Paralysis[1].BrendMode_ALPFA_Array[i] -= 12;
							if (Paralysis[1].BrendMode_ALPFA_Array[i] <= 0)
							{
								Paralysis[1].display_permit_Array[i] = FALSE;
								Paralysis[1].BrendMode_ALPFA_Array[i] = 255;
								continue;
							}
						}
					}
				}
				else 
				{
					if (Tick % 3 == 0) {
						par.Delete_frame++;
					}
					if (par.Delete_frame > 8) {
						par.Delete_display_permit = FALSE;
						par.Delete_frame = 0;
						Tick = 0;
					}
				}
				break;
			}
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

	if (delete_flg)		//値の初期化
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

int NormalBullet::GetDamageParSecond() const
{
	return chemical_formula->damage_per_second;
}

bool NormalBullet::GetDelete_flg() {
	if (exp.Delete_display_permit == TRUE) {
		return true;
	}
	else if (mel.Delete_display_permit == TRUE) 
	{
		return true;
	}
	else if (par.Delete_display_permit == TRUE) {
		return true;
	}
	else if (poi.Delete_display_permit == TRUE) {
		return true;
	}
	else {
		return false;
	}
}

void NormalBullet::Set_exp_Delete_flg(bool b,int x,int y) {
	exp.Delete_display_permit = b;
	exp.Delete_x = x;
	exp.Delete_y = y;
}
void NormalBullet::Set_mel_Delete_flg(bool b, int x, int y) {
	mel.Delete_display_permit = b;
	mel.Delete_x = x;
	mel.Delete_y = y;
}
void NormalBullet::Set_poi_Delete_flg(bool b, int x, int y) {
	poi.Delete_display_permit = b;
	poi.Delete_x = x;
	poi.Delete_y = y;
}
void NormalBullet::Set_par_Delete_flg(bool b, int x, int y) {
	par.Delete_display_permit = b;
	par.Delete_x = x;
	par.Delete_y = y;
}