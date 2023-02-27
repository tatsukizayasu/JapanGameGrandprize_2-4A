#include "EfectBeam.h"
#include "DxLib.h"

EfectBeam::EfectBeam()
{
	location.x = 0;
	location.y = 0;
	filling_radius_x = 50;
	filling_radius_y = 100;
}

void EfectBeam::Draw() const
{
	DrawOval(location.x, location.y, filling_radius_x, filling_radius_y,0x00ff00,FALSE);
}

void EfectBeam::Update(float p_x, float p_y)
{
	location.x = p_x + 50;
	location.y = p_y + 20;
	filling_radius_x--;
	filling_radius_y -= 2;
}