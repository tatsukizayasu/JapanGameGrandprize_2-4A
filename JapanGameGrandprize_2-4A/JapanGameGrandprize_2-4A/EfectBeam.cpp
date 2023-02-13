#include "EfectBeam.h"
#include "DxLib.h"



EfectBeam::EfectBeam()
{
	location.x = 0;
	location.y = 0;
	filling_radius = 50;
}

void EfectBeam::Draw() const
{

}

void EfectBeam::Update(float p_x, float p_y)
{
	location.x = p_x + 20;
	location.y = p_y + 20;
	filling_radius--;
}
