#include "Element_Wooden_Floor.h"
#include "../Player.h"
#include "../PadInput.h"
#include "Stage_Element.h"


Element_Wooden_Floor::Element_Wooden_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : Stage_Element_Base(element, image, location, area)
{
	this->type = Element::DEBUG_GRASS;
	original_collision = area;
	original_image = *image;

	//*image = LoadGraph("Images/Stage/Wooden_Floor.png");
	area = { MAP_CHIP_SIZE, MAP_CHIP_SIZE };
}

Element_Wooden_Floor::~Element_Wooden_Floor()
{
}

void Element_Wooden_Floor::Update(Player* player)
{
	//プレイヤーが上にいる場合、当たり判定範囲を0にする
	if (HitPlayer(player)) {
		//左スティックを下方向に倒している
		if (PAD_INPUT::GetLStick().y <= -10000)
		{
			area = { -MAP_CHIP_SIZE, -MAP_CHIP_SIZE };
			SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
			image = 0;
		}
	}
	//プレイヤーがマップチップよりも下に行ったら元の当たり判定範囲に戻す
	else if (player->GetLocation().y > location.y) {
		area = original_collision;
		image = original_image;
	}

	//当たり判定範囲のデバック表示
	//printfDx("x:%f, y:%f\n", mapchip->GetArea().height, mapchip->GetArea().width);
}

void Element_Wooden_Floor::Draw() const
{

	MapChip::Draw();
}
