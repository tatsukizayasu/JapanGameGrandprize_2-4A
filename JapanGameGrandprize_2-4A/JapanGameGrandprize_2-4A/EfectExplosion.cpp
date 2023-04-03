#include "EfectExplosion.h"
#include "DxLib.h"
#include <math.h>

//-----------------------------------
// コンストラクタ
//-----------------------------------
EfectExplosion::EfectExplosion()
{

	location.x = 0.0;
	location.y = 0.0;
	trance = 0;
	magni = 0;

	delete_flg = false;

	explosion_image = 0;
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
EfectExplosion::EfectExplosion(float b_x, float b_y)
{

	location.x = b_x;
	location.y = b_y;
	trance = 255;
	magni = 0;

	delete_flg = false;

	if ((explosion_image = LoadGraph("Images/Player/explosion.png")) == -1)
	{
		throw "err explosion.png";
	}
}

//-----------------------------------
// 描画
//-----------------------------------
void EfectExplosion::Draw() const
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trance);
	DrawRotaGraph(location.x, location.y, magni, 0, explosion_image, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//-----------------------------------
// 更新
//-----------------------------------
void EfectExplosion::Update()
{

	if (trance > 0)
	{
		trance -= 20;
	}
	else
	{
		delete_flg = true;
	}

	magni++;
}