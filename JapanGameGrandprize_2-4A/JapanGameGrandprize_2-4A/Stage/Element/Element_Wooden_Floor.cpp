#include "Element_Wooden_Floor.h"
#include "../CameraWork.h"

Element_Wooden_Floor::~Element_Wooden_Floor()
{


}

Element_Wooden_Floor::Element_Wooden_Floor(const int* p_image, Location location, Area area)
{
	this->location.x = location.x;
	this->location.y = location.y;

	this->area.width = area.width;
	this->area.height = area.height;

	image = *p_image;
	{
		int x;
		int y;
		GetGraphSize(image, &x, &y);
		if (x == y)
		{
			ex_rate = area.height / y;
		}
		else
		{
			ex_rate = MAP_CHIP_SIZE / y;
		}
		image_size.width = (float)x;
		image_size.height = (float)y;
	}

	//collision_dir = { 0,0 };

}

//-----------------------------------
// çXêV
//-----------------------------------
void Element_Wooden_Floor::Update(Player* player)
{

	//if (HitBox(player)) {
	//	//è„
	//	if (location.y < player->GetLocation().y) {
	//		collision_dir.y = 1;
	//	}
	//	//â∫
	//	else if (location.y > player->GetLocation().y) {
	//		collision_dir.y = -1;
	//	}



	//	//âE
	//	if (location.x > player->GetLocation().x) {
	//		collision_dir.x = 1;
	//	}

	//	//ç∂
	//	else if (location.x < player->GetLocation().x) {
	//		collision_dir.x = -1;
	//	}

	//}
}

//-----------------------------------
// ï`âÊ
//-----------------------------------
void Element_Wooden_Floor::Draw()const
{
	//printfDx("camera_x:%f\tcamera_y:%f\n", CameraWork::GetCamera().x, CameraWork::GetCamera().y);
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	DrawRotaGraphF(x, y, ex_rate, 0, image, TRUE);
#ifdef _SHOW_COLLISION
	DrawCollision();
#endif


}

//-----------------------------------
// 
//-----------------------------------