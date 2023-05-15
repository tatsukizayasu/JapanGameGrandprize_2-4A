#include "Bullet.h"
#include "DxLib.h"
#include "player.h"
#include "CameraWork.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
BulletBase::BulletBase()
{

	efect_end = false;
	delete_flg = false;
	efect_explosion = nullptr;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
BulletBase::BulletBase(float player_x, float player_y)
{

	delete_flg = false;
	efect_explosion = nullptr;
}

bool BulletBase::GetEfectFlg() const
{

	return efect_end;
}

int BulletBase::GetDamage() const
{
	 
	return damage;
}

int BulletBase::GetDebuffTime() const
{

	return debuff_time;
}

ATTRIBUTE BulletBase::GetAttribute() const
{

	return attribute;
}

bool BulletBase::HitBlock(const Stage* stage_pointa)
{

	//マップチップ
	std::vector<MapChip*>map_chip = stage_pointa->GetMapChip();

	//描画範囲
	Location camera = CameraWork::GetCamera();

	for (MapChip* map_chip : map_chip)
	{
		if (map_chip != nullptr)
		{

			Location draw_location = map_chip->GetLocation();
			Area draw = { SCREEN_HEIGHT + CHIP_SIZE,SCREEN_WIDTH + CHIP_SIZE };

			// 画面内にあるMapChipオブジェクトだけUpdateする
			if ((camera.x < draw_location.x + draw.width) && (draw_location.x < camera.x + draw.width)
				&& (camera.y < draw_location.y + draw.height) && (draw_location.y < camera.y + draw.height))
			{
				if (HitBox(map_chip))
				{
					return true;
				}
			}
		}
	}
	return false;
}