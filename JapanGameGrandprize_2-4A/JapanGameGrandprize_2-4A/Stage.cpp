#include "Stage.h"
#include "DxLib.h"

Stage::Stage() {
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}

	for (int i = 0; i < 32;i++) {
		mapchip.push_back(new MapChip(&block_images[0],
			{ (i * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2),
			SCREEN_HEIGHT - MAP_CHIP_SIZE / 2 }, 
			{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
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
