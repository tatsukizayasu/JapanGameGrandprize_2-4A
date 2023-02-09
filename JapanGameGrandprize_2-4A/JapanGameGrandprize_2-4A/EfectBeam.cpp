//#include "EfectBeam.h"
//#include "DxLib.h"
//
//
//
//EfectBeam::EfectBeam()
//{
//	
//	for (int i = 0; i < 3; i++)
//	{
//		location[i].x = 0;
//		location[i].y = 0;
//		radius[i] = 10 * i;
//	}
//
//	add_loc_y[0] = 5;
//	add_loc_y[1] = -5;
//	add_loc_y[2] = -5;
//
//	shoot_count = 0;
//}
//
//void EfectBeam::Draw() const
//{
//	for (int i = 0; i < 3; i++)
//	{
//		DrawCircle(location[i].x, location[i].y, radius[i],0xff00ff);
//	}
//}
//
//void EfectBeam::Update(float p_x, float p_y)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		location[i].x = p_x + 60;
//		location[i].y = p_y + (20 * i);
//
//		if (location[i].y < p_y)
//		{
//			location[i].y = p_y;
//			add_loc_y[i] = add_loc_y[i] * -1;
//		}
//		else if (location[i].y > p_y + 40)
//		{
//			location[i].y = p_y + 40;
//			add_loc_y[i] = add_loc_y[i] * -1;
//		}
//		
//		radius[i] += 3;
//		if (radius[i] > RADIUS_MAX)
//		{
//			radius[i] = RADIUS_MAX;
//		}
//	}
//}
