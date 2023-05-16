#include "LastBossBarrier.h"
#include "DxLib.h"
#include "CameraWork.h"
#include "NormalBullet.h"

//耐久値
#define DURABILITY 500

//画像枚数
#define BARRIER_NUM 14

//エフェクトの本体のアニメーション
#define BARRIER_ANIMATION 2



//-----------------------------------
//コンストラクタ
//-----------------------------------
LastBossBarrier::LastBossBarrier(const Location spawn_location)
{
	end_deployment = false;

	location = spawn_location;
	radius = 160;
	images = new int[14];

	LoadDivGraph("Images/Enemy/SpecialMoves/barrier2_2.png", BARRIER_NUM, 2, 7, 384, 383,images);

	for (int i = 0; i < BARRIER_VOLUME; i++)
	{
		animation[i] = 0;
	}
	size = 2.0;
	angle = 0.0;
	count = 0;
	durability = DURABILITY;
	old_durability = durability;
	volume = BARRIER_VOLUME;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
LastBossBarrier::~LastBossBarrier()
{
	for (int i = 0; i < BARRIER_NUM; i++)
	{
		DeleteGraph(images[i]);
	}
	delete[] images;
}

//-----------------------------------
//更新
//-----------------------------------
void LastBossBarrier::Update()
{
	count++;

	if (!end_deployment)
	{
		Deployment();
	}
	else
	{
		if ((durability / 20) < (old_durability / 20))
		{
			for (int i = 0; i < ((old_durability / 20) - (durability / 20)); i++)
			{
				animation[volume - 1]++;
				volume--;
				if (volume <= 1)
				{
					volume = BARRIER_VOLUME;
				}
			}
			
		}
		old_durability = durability;
	}
}
//バリアの展開
void LastBossBarrier::Deployment()
{
	int end_deployment_count = 0;

	if (count % BARRIER_ANIMATION == 0)
	{
		for (int i = 0; i < BARRIER_VOLUME; i++)
		{
			if (animation[i] < 9)
			{
				animation[i]++;
			}
			else
			{
				end_deployment_count++;

			}
		}
	}

	if (BARRIER_VOLUME <= end_deployment_count)
	{
		end_deployment = true;
		animation[0] = 11;
	}
}
//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
void LastBossBarrier::HitBullet(const BulletBase* bullet)
{
	durability -= bullet->GetDamage();
	if (durability < 0)
	{
		durability = 0;
	}
}

//-----------------------------------
//描画
//-----------------------------------
void LastBossBarrier::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
	for (int i = 0; i < BARRIER_VOLUME; i++)
	{
		if (animation[i] <BARRIER_NUM)
		{
			DrawRotaGraphF(draw_location.x, draw_location.y, size, angle, images[animation[i]], TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}

//-----------------------------------
//耐久値バーの描画
//-----------------------------------
void LastBossBarrier::DrawDurabilityBar() const
{
	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x000000, TRUE);
	DrawBox(160, 10, 160 + (960 * (static_cast<float>(durability) / DURABILITY)), 40, 0xffffff, TRUE);
	DrawBox(160, 10, SCREEN_WIDTH - 160, 40, 0x8f917f, FALSE);
}

//-----------------------------------
//破壊された
//-----------------------------------
bool LastBossBarrier::Break() const
{
	bool ret = false;

	if (durability <= 0)
	{
		ret = true;
	}

	return ret;
}