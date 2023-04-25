#include "EnemyBase.h"
#include "DxLib.h"
#include "vector"
#include "CameraWork.h"

int EnemyBase::log_font[4];

//-----------------------------------
//コンストラクタ
//-----------------------------------
EnemyBase::EnemyBase() 
{

	can_delete = false;
	left_move = true;
	poison = false;
	paralysis = false;
	hp = 0;
	speed = 0;
	damage = 0;
	paralysis_time = 0;
	poison_damage = 0;
	poison_time = 0;
	drop_volume = 0;
	drop_type_volume = 0; 

	drop_element = nullptr;

	kind = ENEMY_KIND::NONE; 
	state = ENEMY_STATE::IDOL;
	type = nullptr;
	images = nullptr;
	
	InitDamageLog();
}

//ログ用のフォントの作成
void EnemyBase::CreateLogFont()
{
	log_font[0] = CreateFontToHandle("Weakness", 24, 1, DX_FONTTYPE_NORMAL);
	log_font[1] = CreateFontToHandle("Nomal", 20, 1, DX_FONTTYPE_NORMAL);
	log_font[2] = CreateFontToHandle("Resistance", 20, 1, DX_FONTTYPE_NORMAL);
	log_font[3] = CreateFontToHandle("Invalid", 16, 1, DX_FONTTYPE_NORMAL);
}

//ログ用のフォントの削除
void EnemyBase::DeleteLogFont()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteFontToHandle(log_font[i]);
	}
}
//-----------------------------------
// HPが0かどうか判断(0になったらtrue)
//-----------------------------------
bool EnemyBase::CheckHp()
{

	bool ret = false;

	if (hp <= 0)
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
//画面外に出た
//-----------------------------------
bool EnemyBase::ScreenOut()
{

	bool ret = false; //戻り値
	Location scroll; //画面スクロールを考慮した座標
	Location camera = CameraWork::GetCamera(); //カメラ
	scroll = location - camera;

	if ((scroll.x < -area.width) || ((SCREEN_WIDTH + area.width) < scroll.x) ||
		(scroll.y < -area.height) || ((SCREEN_HEIGHT + area.height) < scroll.y))
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
//ステージとの当たり判定
//-----------------------------------
HitMapChip EnemyBase::HitStage(const Stage* stage)
{

	HitMapChip ret = { false,nullptr }; //戻り値

	//マップチップ
	std::vector<MapChip*>map_chip = stage->GetMapChip();

	for (MapChip* chip : map_chip)
	{
		if (chip != nullptr)
		{
			Location chip_location = chip->GetLocation();
			Area chip_area = chip->GetArea();

			if ((location.x - (area.width / 2) <= chip_location.x + (chip_area.width / 2)) &&
				(chip_location.x - (chip_area.width / 2) <= location.x + (area.width / 2)))
			{
				if (HitBox(chip))
				{
					ret.hit = true;
					ret.chip = chip;
					break;
				}
			}
		}
	}

	return ret;
}

//-----------------------------------
//ステージのどの面と当たったを判断
//-----------------------------------
STAGE_DIRECTION EnemyBase::HitDirection(const MapChip* map_chip)
{

	STAGE_DIRECTION ret = STAGE_DIRECTION::TOP; //戻り値

	Location chip_location = map_chip->GetLocation();
	Area chip_area = map_chip->GetArea();
	Location vertex = location; //頂点
	float distance[4]; //距離
	int min_vertex; //当たった頂点
	float min_distance; //最低距離

	//左上との距離
	distance[0] = sqrtf(powf(chip_location.x - (location.x + area.width / 2), 2) +
		powf(chip_location.y - (location.y - area.height / 2), 2));

	//右上との距離
	distance[1] = sqrtf(powf(chip_location.x - (location.x - area.width / 2), 2) +
		powf(chip_location.y - (location.y - area.height / 2), 2));

	//左下との距離
	distance[2] = sqrtf(powf(chip_location.x - (location.x - area.width / 2), 2) +
		powf(chip_location.y - (location.y + area.height / 2), 2));

	//右下との距離
	distance[3] = sqrtf(powf(chip_location.x - (location.x + area.width / 2), 2) +
		powf(chip_location.y - (location.y + area.height / 2), 2));

	min_distance = distance[0];
	min_vertex = 0;

	for (int i = 1; i < 4; i++)
	{
		if (distance[i] < min_distance)
		{
			min_distance = distance[i];
			min_vertex = i;
		}
	}
	
	switch (min_vertex)
	{
	case 0:
		vertex = { location.x - (area.width / 4),location.y - (area.height / 4) };
		break;
	case 1:
		vertex = { location.x + (area.width / 4),location.y - (area.height / 4) };
		break;
	case 2:
		vertex = { location.x - (area.width / 4),location.y + (area.height / 4) };
		break;
	case 3:
		vertex = { location.x + (area.width / 4),location.y + (area.height / 4) };
		break;
	default:
		break;
	}

	//上面との距離
	distance[0] = sqrtf(powf(chip_location.x - vertex.x, 2) +
		powf((chip_location.y - CHIP_SIZE / 2) - vertex.y, 2));

	//下面との距離
	distance[1] = sqrtf(powf(chip_location.x - vertex.x, 2) +
		powf((chip_location.y + CHIP_SIZE / 2) - vertex.y, 2));

	//左面との距離
	distance[2] = sqrtf(powf((chip_location.x - CHIP_SIZE / 2) - vertex.x, 2) +
		powf(chip_location.y - vertex.y, 2));

	//右面との距離
	distance[3] = sqrtf(powf((chip_location.x + CHIP_SIZE / 2) - vertex.x, 2) +
		powf(chip_location.y - vertex.y, 2));

	min_distance = distance[0];
	for (int i = 1; i < 4; i++)
	{
		if (distance[i] < min_distance)
		{
			min_distance = distance[i];
			ret = static_cast<STAGE_DIRECTION>(i);
		}
	}

	return ret;
}

//-----------------------------------
//毒状態の処理
//-----------------------------------
void EnemyBase::Poison()
{

	if (poison)
	{
		poison_time--;
		if (0 < poison_time)
		{
			if (poison_time % POISON_DAMAGE_FLAME == 0)
			{
				hp -= poison_damage;
			}
		}
		else
		{
			poison = false;
		}
	}
}

//-----------------------------------
//麻痺状態の処理
//-----------------------------------
void EnemyBase::Paralysis()
{

	if (paralysis)
	{
		paralysis_time--;
		if (paralysis_time < 0)
		{
			paralysis = false;
		}
	}
}

//ダメージログの更新
void EnemyBase::UpdateDamageLog()
{
	for (int i = 0; i < LOG_NUM; i++)
	{
		if (!damage_log[i].log)
		{
			break;
		}

		damage_log[i].time--;

		if (damage_log[i].time < 0)
		{
			damage_log[i].log = false;
			for (int j = i + 1; j < LOG_NUM; j++)
			{
				if (!damage_log[j].log)
				{
					break;
				}

				damage_log[j - 1] = damage_log[j];
				damage_log[j].log = false;
			}
			i--;
		}
	}
}


//-----------------------------------
//HPバーの描画
//-----------------------------------
void EnemyBase::DrawHPBar(const int max_hp) const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;
	DrawBox(draw_location.x - max_hp / 4, draw_location.y - 80,
		draw_location.x + max_hp / 4 + 1, draw_location.y - 70, 0x000000, TRUE);
	DrawBox(draw_location.x - max_hp / 4, draw_location.y - 80,
		draw_location.x - max_hp / 4 + (max_hp / 2 * (static_cast<float>(hp) / max_hp)), draw_location.y - 70, 0x07ff00, TRUE);
	DrawBox(draw_location.x - max_hp / 4, draw_location.y - 80,
		draw_location.x + max_hp / 4 + 1, draw_location.y - 70, 0x8f917f, FALSE);
}

//-----------------------------------
//ダメージログの描画
//-----------------------------------
void EnemyBase::DrawDamageLog()const
{
	int color = 0;
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	for (int i = 0; i < LOG_NUM; i++)
	{
		if (!damage_log[i].log)
		{
			break;
		}
		switch (damage_log[i].congeniality)
		{
		case CONGENIALITY::WEAKNESS:	//弱点
			color = 0xff0000;
			break;
		case CONGENIALITY::NOMAL:
			color = 0xffffff;
			break;
		case CONGENIALITY::RESISTANCE:	//耐性
			color = 0xc0c0c0;
			break;
		case CONGENIALITY::INVALID:		//無効
			color = 0xa1a3a6;
			break;
		default:
			break;
		}

		DrawFormatStringToHandle(draw_location.x - 20, draw_location.y - 110 - (LOG_TIME - damage_log[i].time),
			color, log_font[static_cast<int>(damage_log[i].congeniality)],
			"%3d", damage_log[i].damage);

	}
}

//-----------------------------------
//ドロップする種類の量の取得
//-----------------------------------
int EnemyBase::GetDropTypeVolume() const
{

	return drop_type_volume;
}

//-----------------------------------
//ドロップするアイテムの量の取得
//-----------------------------------
int EnemyBase::GetDropVolume() const
{

	return drop_volume;
}

//-----------------------------------
// ドロップアイテムの取得
//-----------------------------------
ElementItem EnemyBase::GetDropItem(int i) const
{ 

	return *drop_element[i]; 
}

//-----------------------------------
// エネミーの種類の取得
//-----------------------------------
ENEMY_KIND EnemyBase::GetEnemyKind() const
{

	return kind;
}

//-----------------------------------
//エネミーの状態の取得
//-----------------------------------
ENEMY_STATE EnemyBase::GetState()const
{

	return state;
}

//-----------------------------------
//削除可能状態の取得
//-----------------------------------
bool EnemyBase::GetCanDelete() const
{

	return can_delete;
}

//-----------------------------------
//ダメージログの初期化
//-----------------------------------
void EnemyBase::InitDamageLog()
{
	for (int i = 0; i < LOG_NUM; i++)
	{
		damage_log[i].log = false;
		damage_log[i].damage = -1;
		damage_log[i].congeniality = CONGENIALITY::NOMAL;
	}
}