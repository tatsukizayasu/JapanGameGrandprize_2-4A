#include "DxLib.h"
#include "StageBuilder.h"

//------------------------------------
// コンストラクタ
//------------------------------------
StageBuilder::StageBuilder()
{
	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) {
		throw "Images/Stage/map_chips_test.png";
	}
	mouse_pos = {};
}

//------------------------------------
// デストラクタ
//------------------------------------
StageBuilder::~StageBuilder()
{
	for (int i = 0; i < map_chips.size(); i++)
	{
		delete map_chips[i];
	}
	map_chips.clear();
}

//------------------------------------
// 更新
//------------------------------------
void StageBuilder::Update()
{
	KeyManager::Update(); //StageBuilder上でしか使わないため、ソースコードの散らばりを避けています。
	MouseUpdate();
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		MakeMapChip();
	}
}

//------------------------------------
// 描画
//------------------------------------
void StageBuilder::Draw()const
{
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 2, 10, 0xFFFFFF);
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 1, 10, 0x000000);

	for (int i = 0; i < map_chips.size(); i++)
	{
		map_chips[i]->Draw();
	}

	DrawFrame();
}

//------------------------------------
// マウスの更新
//------------------------------------
void StageBuilder::MouseUpdate()
{
	int x, y;
	GetMousePoint(&x, &y);
	mouse_pos.x = (float)x;
	mouse_pos.y = (float)y;
}

//------------------------------------
// 格子の描画
//------------------------------------
void StageBuilder::DrawFrame()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_HEIGHT; i++)
	{
		DrawLine(0, i * MAP_CHIP_SIZE, SCREEN_WIDTH, i * MAP_CHIP_SIZE, 0xFFFFFF);
	}

	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_WIDTH; i++)
	{
		DrawLine(i * MAP_CHIP_SIZE, 0, i * MAP_CHIP_SIZE, SCREEN_HEIGHT, 0xFFFFFF);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//------------------------------------
// マップチップの作成
//------------------------------------
void StageBuilder::MakeMapChip()
{
	map_chips.push_back(new MapChip(&block_images[0],
		{ mouse_pos.x,mouse_pos.y },
		{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// 
//------------------------------------
