#include "Stage.h"
#include "../CameraWork.h"
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Player.h"
#include "Element/Stage_Element.h"

#define STAGE_NAME	"debugStage";
#define STAGE_NAME	"sample_stage2";
#define STAGE_NAME	"Stage01";

//-----------------------------------
// コンストラクタ
//-----------------------------------
Stage::Stage()
{

	element = new Stage_Element();

	if (LoadDivGraph("Images/Stage/map_chips.png", 110, 10, 11, CHIP_SIZE, CHIP_SIZE, block_images + 1) == -1)
	{
		throw "Images/Stage/map_chips.png";
	}

	//マップデータの読み込み
	LoadMap();

	//マップチップの描画情報をセット
	for (float y = 0; y < map_data.size(); y++)
	{
		for (float x = 0; x < map_data.at(0).size(); x++)
		{
			int i = map_data.at(y).at(x);
			if (i != 0 && i != -1)
			{
				mapchip.push_back(new MapChip
				(&block_images[i],
					{
						x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
						y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
					}, { CHIP_SIZE,CHIP_SIZE }));
				
				
				element->AddElement(mapchip.back(), &block_images[i], i);
			}
			/*else
			{
				mapchip.push_back(nullptr);
			}*/
		}
	}

	collision_chip = { 0, 0 };
	collision_dir = { 0, 0 };

#ifdef _STAGE_BUILDER
	stage_builder = new StageBuilder();
#endif
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Stage::~Stage()
{

	//マップチップの描画情報オブジェクトを削除
	for (int i = 0; i < mapchip.size(); i++)
	{
		delete mapchip.at(i);
	}

	mapchip.clear();
	mapchip.shrink_to_fit();

	//マップチップ画像を削除
	for (int i = 0; i < 100; i++)
	{
		DeleteGraph(block_images[i]);
	}

#ifdef _STAGE_BUILDER
	delete stage_builder;
#endif
}

//-----------------------------------
// 更新
//-----------------------------------
void Stage::Update(Player* player)
{

	//当たり判定演算範囲
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& m : mapchip)
	{
		if (m == nullptr) continue;

		float x = m->GetLocation().x;
		float y = m->GetLocation().y;
		float w = m->GetArea().width;
		float h = m->GetArea().height;

		//ブロックの範囲を固定化
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// 画面内にあるMapChipオブジェクトだけUpdateする
		if (x + w < camera.x || camera.x + draw.width < x || y + h < camera.y || camera.y + draw.height < y) continue;

		//当たっているオブジェクトの座標を更新
		collision_dir = m->GetMapChip_Collision();
		if (collision_dir.x != 0 || collision_dir.y != 0) {
			collision_chip.x = m->GetLocation().x;
			collision_chip.y = m->GetLocation().y;
			break;
		}

		m->Update(player);
		element->Update(player);

		//当たっている方向を更新
		collision_dir = m->GetMapChip_Collision();
		if (collision_dir.y != 0) {
			//clsDx();
			//printfDx("当たった:X%d\tY:%d\n", collision_dir.x, collision_dir.y);
			collision_dir_w = collision_dir;

			if (collision_dir.x != 0) {
				//speed_x = 0.0f;
			}

		}

	}

#ifdef _STAGE_BUILDER
	stage_builder->Update();
#endif
}

//-----------------------------------
// 描画
//-----------------------------------
void Stage::Draw()
{

	//マップチップ		描画

	//描画範囲
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& m : mapchip)
	{
		if (m == nullptr) continue;

		float x = m->GetLocation().x;
		float y = m->GetLocation().y;
		float w = m->GetArea().width;
		float h = m->GetArea().height;

		//ブロックの範囲を固定化
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// 画面内にあるMapChipオブジェクトだけ描画する
		if (x + w < camera.x || camera.x + draw.width < x || y + h < camera.y || camera.y + draw.height < y) continue;

		m->Draw();
		element->Draw();
	}


#ifdef _STAGE_BUILDER
	stage_builder->Draw();
#endif
}

//-----------------------------------
// マップ読込み
//-----------------------------------
void Stage::LoadMap()
{
	const char* stage_name = STAGE_NAME;

	char buf[37];
	sprintf_s(buf, sizeof(buf), "Data/Map_Data/%s.csv", stage_name);

	int FileHandle;

	if ((FileHandle = FileRead_open(buf)) == 0)
	{
		exit(1);
	}

	char str[2506];		//一行の長さ
	char* context;
	int i = 0, j = 0;

	while (FileRead_gets(str, sizeof(str), FileHandle) != -1)
	{

		char* tmp = strtok_s(str, ",", &context);

		map_data.push_back(std::vector<int>());

		while (tmp != NULL)
		{

			map_data[i].push_back(std::stoi(tmp));

			tmp = strtok_s(NULL, ",", &context);
			j++;
		}

		j = 0;
		i++;
	}

	FileRead_close(FileHandle);
}
