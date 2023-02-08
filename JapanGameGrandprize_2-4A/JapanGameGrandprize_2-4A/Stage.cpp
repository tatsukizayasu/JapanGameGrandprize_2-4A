#include "Stage.h"
#include "DxLib.h"
#define STAGE_BUILDER

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
	for (int i = 0; i < 32; i++) {
		mapchip[i]->Update();
	}

#ifdef STAGE_BUILDER
	stage_builder->Update();
	MakeMapChip();
#endif
}

void Stage::Draw()
{
	for (int i = 0; i < 32; i++) {
		mapchip[i]->Draw();
	}

#ifdef STAGE_BUILDER
	stage_builder->Draw();
#endif
	
}

void Stage::LoadMap()
{
}


#ifdef STAGE_BUILDER
void Stage::MakeMapChip()
{
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		mapchip.push_back(stage_builder->MakeMapChip());
	}
}
#endif