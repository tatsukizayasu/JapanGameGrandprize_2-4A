#include "Stage.h"
#include "DxLib.h"
#define STAGE_BUILDER

Stage::Stage() {
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}

	for (int i = 0; i < 32;i++) {
		mapchip.push_back(new MapChip(&block_images[0],
			{ i * MAP_CHIP_SIZE,SCREEN_HEIGHT - MAP_CHIP_SIZE },
			{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
	}

#ifdef STAGE_BUILDER
	stage_builder = new StageBuilder();
#endif
}


Stage::~Stage() {

	//delete mapchip;

#ifdef STAGE_BUILDER
	delete stage_builder;
#endif
}

void Stage::Update()
{
	for (int i = 0; i < mapchip.size(); i++) {
		mapchip.at(i)->Update();
	}

#ifdef STAGE_BUILDER
	stage_builder->Update();
#endif
}

void Stage::Draw()
{
	for (int i = 0; i < mapchip.size(); i++) {
		mapchip.at(i)->Draw();
	}

#ifdef STAGE_BUILDER
	stage_builder->Draw();
#endif
	
}

void Stage::LoadMap()
{
}