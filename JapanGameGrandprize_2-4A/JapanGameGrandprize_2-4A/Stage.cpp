#include "Stage.h"
#include "DxLib.h"

Stage::Stage() {
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}

	for (float y = 0; y < 18; y++) {
		for (float x = 0; x < 32; x++) {
			mapchip.push_back(new MapChip(&block_images[0], { x * MAP_CHIP_SIZE,y * MAP_CHIP_SIZE}, { 40,40 }));
		}
	}
}


Stage::~Stage() {

	//delete mapchip;
}

void Stage::Update()
{
	for (int i = 0; i < mapchip.size(); i++) {		
		mapchip.at(i)->Update();
	}
}

void Stage::Draw()
{
	for (int i = 0; i < mapchip.size(); i++) {
		mapchip.at(i)->Draw();
	}
	
	
}

void Stage::LoadMap()
{
}
