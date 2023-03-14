#include "EnemyBulletBase.h"
#include "Define.h"
#include "CameraWork.h"
#include "Stage/Stage.h"
#include "BULLET.h"

//-----------------------------------
//画面外に出たかどうか
//-----------------------------------
bool EnemyBulletBase::ScreenOut()
{
	bool ret = false; //戻り値
	float x, y;
	x = location.x - CameraWork::GetCamera().x;
	y = location.y - CameraWork::GetCamera().y;

	if ((x < 0) || (SCREEN_WIDTH < x) || (y < 0) || (SCREEN_HEIGHT < y))
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
//ステージとの当たり判定
//-----------------------------------
bool EnemyBulletBase::HitStage(const Stage* stage) const
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
			Location draw_location = chip->GetLocation();
			Area draw = chip->GetArea();

			//描画範囲内にあるブロック
			if ((camera.x < draw_location.x + draw.width) && (draw_location.x < camera.x + draw_area.width) &&
				(camera.y < draw_location.y + draw.height) && (draw_location.y < camera.y + draw_area.height))
			{
				if (HitBox(chip))
				{
					ret = true;
					break;
				}
			}
		}
	}

	return ret;
}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
bool EnemyBulletBase::HitPlayerBullet(const BulletBase* player_bullet) const
{
	bool ret = false; //戻り値
	if (HitSphere(player_bullet))
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
//ダメージの取得
//-----------------------------------
int EnemyBulletBase::GetDamage() const
{
	return damage;
}

//-----------------------------------
//タイプの取得
//-----------------------------------
ENEMY_TYPE EnemyBulletBase::GetType() const
{
	return type;
}