#include "Stage.h"
#include "DxLib.h"

Stage::Stage() {
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}

	for (int i = 0; i < 32;i++) {
		mapchip.push_back(new MapChip(&block_images[0], { i * MAP_CHIP_SIZE,680 }, { 40,40 }));
	}
}


Stage::~Stage() {

	//delete mapchip;
}

void Stage::Update()
{
	for (int i = 0; i < 32; i++) {
		mapchip[i]->Update();
	}
	
}

void Stage::Draw()
{
	for (int i = 0; i < 32; i++) {
		mapchip[i]->Draw();
	}
	
	
}

void Stage::LoadMap()
{
}
