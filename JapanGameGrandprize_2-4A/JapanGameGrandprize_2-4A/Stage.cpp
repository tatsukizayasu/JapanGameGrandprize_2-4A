#include "Stage.h"
#include "DxLib.h"

Stage::Stage() {
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}
}


Stage::~Stage() {

}

void Stage::Update()
{

}

void Stage::Draw()
{
	for (int i = 0; i < 32; i++) {
		for (int j = 16; j < 18; j++) {
		DrawExtendGraph(i * MAP_CHIP_SIZE, j * MAP_CHIP_SIZE, i * MAP_CHIP_SIZE + MAP_CHIP_SIZE, j * MAP_CHIP_SIZE + MAP_CHIP_SIZE,  block_images[0], FALSE);
		}
	}
	
}

void Stage::LoadMap()
{
}
