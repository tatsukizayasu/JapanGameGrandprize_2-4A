#include "Element_Wooden_Floor.h"
#include "../Player.h"
#include "../PadInput.h"

Element_Wooden_Floor::Element_Wooden_Floor(MapChip* mapchip, int* image) : Stage_Element_Base(mapchip, image)
{
	original_collision = mapchip->GetArea();
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
			mapchip->SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
		}
	}
	//プレイヤーがマップチップよりも下に行ったら元の当たり判定範囲に戻す
	else if (player->GetLocation().y > mapchip->GetLocation().y) {
		mapchip->SetArea(original_collision);
	}
	//当たり判定範囲のデバック表示
	//printfDx("x:%f, y:%f\n", mapchip->GetArea().height, mapchip->GetArea().width);
}

void Element_Wooden_Floor::Draw() const
{
}
