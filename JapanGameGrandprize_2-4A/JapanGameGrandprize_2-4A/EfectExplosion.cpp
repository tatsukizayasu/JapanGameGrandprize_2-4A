#include "EfectExplosion.h"
#include "DxLib.h"
#include <math.h>


EfectExplosion::EfectExplosion()
{
	location.x = 0;
	location.y = 0;
	trance = 255;
	magni = 0;

	delete_flg = false;

	if (explosion_image = LoadGraph("Resouce/Images/Player/explosion.png") == -1)
	{
		throw "err explosion.png";
	}
}

void EfectExplosion::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trance);
	DrawRotaGraph(location.x, location.y, magni, 0, explosion_image, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void EfectExplosion::Update()
{
	if (trance > 0)
	{
		trance--;
	}
	else
	{
		delete_flg = true;
	}

	magni++;
}