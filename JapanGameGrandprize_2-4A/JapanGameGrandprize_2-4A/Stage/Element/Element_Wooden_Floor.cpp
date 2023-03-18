#include "Element_Wooden_Floor.h"
#include "../Player.h"
#include "../PadInput.h"
#include "Stage_Element.h"
#include "../CameraWork.h"


Element_Wooden_Floor::Element_Wooden_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->type = type;
	this->location = location;
	this->area = area;
	this->margin_area = { -15.0f,0.0f };
	original_collision = area;

	SetImage(images.at(0));
	original_image = images.at(0);
	
}

Element_Wooden_Floor::~Element_Wooden_Floor()
{
}

void Element_Wooden_Floor::Update(Player* player)
{
	//printfDx("%f\n", GetAnimationTime());
	/*if (GetAnimationTime() > 3.5f) {
		area = { -MAP_CHIP_SIZE, -MAP_CHIP_SIZE };
		image = 0;
	}*/

	//プレイヤーが上にいる場合、当たり判定範囲を0にする
	if (/*HitPlayer(player) && */player->GetLocation().y - player->GetArea().height / 2 - 4.0f < location.y) {
		//左スティックを下方向に倒している
		if (PAD_INPUT::GetLStick().y <= -10000)
		{
			//area = { -MAP_CHIP_SIZE, -MAP_CHIP_SIZE };
			SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
			//SetImage(0);
			
		}
		

	}


	//プレイヤーがマップチップよりも下に行ったら元の当たり判定範囲に戻す
	else if (player->GetLocation().y - player->GetArea().height / 2 - 4.0f> location.y) {
		
		SetArea(original_collision);
		image = original_image;
	}

	//当たり判定範囲のデバック表示
	//printfDx("x:%f, y:%f\n", mapchip->GetArea().height, mapchip->GetArea().width);
}

//void Element_Wooden_Floor::Draw() const
//{
//	float x = location.x - CameraWork::GetCamera().x;
//	float y = location.y - CameraWork::GetCamera().y;
//	DrawRotaGraphF(x, y, 1.0f, 0, image, TRUE);
//}
