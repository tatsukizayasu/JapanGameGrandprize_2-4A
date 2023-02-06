#include "Stage.h"
#include "DxLib.h"

Stage::Stage() {
	if (LoadDivGraph("Resource/Images/Stage/map_chips_test.png", 10, 10, 1, 80, 80, block_images) == -1) {
		throw "Resource/Images/Stage/map_chips_test.png";
	}
}


Stage::~Stage() {

}

void Stage::Update()
{
}

void Stage::Draw()
{
}

void Stage::LoadMap()
{
}
