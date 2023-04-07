#include "Element_Barricade.h"
#include "../Player.h"
#include "../CameraWork.h"

Element_Barricade::Element_Barricade(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{

	this->area = area;
	this->type = type;
	margin_area = { -18.0f,0.0f };
	this->images = images;

	//for (auto& m : element)
	//{
	//	if (this == m.get())continue;

	//	if (GetType() == m->GetType())
	//	{
	//		if (abs(GetLocation().x - m->GetLocation().x) <= MAP_CHIP_SIZE &&
	//			abs(GetLocation().y - m->GetLocation().y) <= MAP_CHIP_SIZE) 
	//		{
	//			if (GetLocation().x < m->GetLocation().x) 
	//			{
	//				Element_Barricade::SetDirection(DIRECTION::LEFT);
	//			}
	//			else if (GetLocation().x > m->GetLocation().x) 
	//			{
	//				Element_Barricade::SetDirection(DIRECTION::RIGHT);
	//			}
	//			else if (GetLocation().y < m->GetLocation().y) 
	//			{
	//				Element_Barricade::SetDirection(DIRECTION::UP);
	//			}
	//			else if (GetLocation().y > m->GetLocation().y) 
	//			{
	//				Element_Barricade::SetDirection(DIRECTION::DOWN);
	//			}
	//			else if(GetLocation().x < m->GetLocation().x && GetLocation().x > m->GetLocation().x ||
	//				GetLocation().y < m->GetLocation().y && GetLocation().y > m->GetLocation().y)
	//			{
	//				Element_Barricade::SetDirection(DIRECTION::CENTER);
	//			}
	//			else 
	//			{
	//				Element_Barricade::SetDirection(DIRECTION::NONE);
	//			}
	//		}
	//	}
	//}

}

Element_Barricade::~Element_Barricade()
{

}

void Element_Barricade::Update(Player* player)
{

}

void Element_Barricade::Draw()const
{

	//âÊëúÇ™Ç»Ç¢ñîÇÕÉGÉâÅ[ÇÃèÍçáÇÕï`âÊÇµÇ»Ç¢
	if (image == 0) { return; }

	//printfDx("camera_x:%f\tcamera_y:%f\n", CameraWork::GetCamera().x, CameraWork::GetCamera().y);
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	//DrawRotaGraphF(x, y, 1.0f, 0, image, TRUE);
	//DrawFormatStringF(x, y, 0xFFFFFF, "%d", direction);
}