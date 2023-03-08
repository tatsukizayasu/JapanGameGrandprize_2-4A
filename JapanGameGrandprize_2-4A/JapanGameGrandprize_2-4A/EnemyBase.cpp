#include "DxLib.h"
#include "EnemyBase.h"
#include "Stage/Stage.h"
#include "vector"
#include "CameraWork.h"

//-----------------------------------
//コンストラクタ
//-----------------------------------
EnemyBase::EnemyBase() 
{
	can_delete = false;
	left_move = true;
	hp = 0;
	speed = 0;
	paralysis_time = 0;
	poison_damage = 0;
	poison_time = 0;
	drop_volume = 0;
	drop_type_volume = 0; 

	drop_element = nullptr;

	kind = ENEMY_KIND::NONE; 
	state = ENEMY_STATE::IDOL;
	type = nullptr;
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
//ステージとの当たり判定
//-----------------------------------
bool EnemyBase::HitStage(const Stage* stage)
{
	bool ret = false; //戻り値

	//マップチップ
	std::vector<MapChip*>map_chip = stage->GetMapChip();

	//カメラの位置
	Location camera = CameraWork::GetCamera();

	//描画範囲の設定
	Area draw_area = { SCREEN_HEIGHT + CHIP_SIZE,SCREEN_WIDTH + CHIP_SIZE };

	for (MapChip* chip : map_chip)
	{
		if (chip != nullptr)
		{
			Location chip_location = chip->GetLocation();
			Area chip_area = chip->GetArea();

			//描画範囲内にあるブロック
			if ((camera.x < chip_location.x + chip_area.width) && (chip_location.x < camera.x + draw_area.width) &&
				(camera.y < chip_location.y + chip_area.height) && (chip_location.y < camera.y + draw_area.height))
			{
				if (HitBox(chip))
				{
					if (state == ENEMY_STATE::MOVE)
					{
						if ((chip_location.y + chip_area.height / 2) < (location.y + area.height / 2))
						{
							if (left_move)
							{
								location.x = (chip_location.x + (chip_area.width / 2) + (area.width / 2) + 2);
							}
							else
							{
								location.x = (chip_location.x - (chip_area.width / 2) - (area.width / 2) - 2);
							}
							left_move = !left_move;
							speed = -speed;
						}
					}
					if (state == ENEMY_STATE::FALL) //落下状態
					{
						location.y = (chip_location.y - (chip_area.height / 2) - (area.height / 2)) + 2;
					}

					ret = true;
					break;
				}
			}
		}
	}

	return ret;
}

//-----------------------------------
//毒状態の処理
//-----------------------------------
void EnemyBase::Poison()
{
	if (0 < poison_time)
	{
		poison_time--;
		if (poison_time % POISON_DAMAGE_FLAME == 0)
		{
			hp -= poison_damage;
		}
	}
}

//-----------------------------------
//麻痺状態の処理
//-----------------------------------
void EnemyBase::Paralysis()
{
	if (0 < paralysis_time)
	{
		paralysis_time--;
		speed *= 0.7;
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
int EnemyBase::GetDropVolume()const
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