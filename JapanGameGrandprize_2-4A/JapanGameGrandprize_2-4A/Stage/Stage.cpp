#include "Stage.h"
#include "../CameraWork.h"
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Player.h"
#include "../CameraWork.h"
#include "Element/Stage_Element.h"

#define STAGE_NAME	"debugStage";
#define STAGE_NAME	"sample_stage2";
#define STAGE_NAME	"Stage01";
//#define STAGE_NAME  "Stage01_test";
//#define STAGE_NAME "Stage02";

//-----------------------------------
// コンストラクタ
//-----------------------------------
Stage::Stage()
{

	element = new Stage_Element();
	this->camera_work = camera_work;

	//スポーン地点に初期値をセット
	spawn_point = { MAP_CHIP_SIZE / 2, SCREEN_HEIGHT / 2 };

	if (LoadDivGraph("Images/Stage/map_chips.png", 50, 10, 5, CHIP_SIZE, CHIP_SIZE, block_images + 1) == -1)
	{
		throw "Images/Stage/map_chips.png";
	}

	if (LoadDivGraph("Images/Stage/stage1_blocks.png", 10, 5, 2, CHIP_SIZE, CHIP_SIZE, stage1_block_images) == -1)
	{
		throw "Images/Stage/stage1_blocks.png";
	}

	//マップデータの読み込み
	LoadMap();

	InitStage();

	//ステージ要素のパラメーターを設定
	element->SetElementParameter();

	//フラグリセット
	is_halfway_point = false;

#ifdef _STAGE_BUILDER
	stage_builder = new StageBuilder();
#endif
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Stage::~Stage()
{

	// マップチップ画像を削除
	for (int i = 0; i < 50; i++)
	{
		DeleteGraph(block_images[i]);
	}

	//vectorの解放

	// map_data内の各vectorを解放
	for (auto& inner_vec : map_data) {
		inner_vec.clear();
		inner_vec.shrink_to_fit();
	}

	// map_data自体を解放
	map_data.clear();
	map_data.shrink_to_fit();

	// MapChipオブジェクトを解放
	for (MapChip* chip : mapchip) {
		delete chip;
	}

	// mapchip自体を解放
	mapchip.clear();
	mapchip.shrink_to_fit();

	enemy_init_location.clear();
	enemy_init_location.shrink_to_fit();

	delete element;

#ifdef _STAGE_BUILDER
	delete stage_builder;
#endif
}

//-----------------------------------
// 更新
//-----------------------------------
void Stage::Update(Player* player)
{
	// 中間地点との当たり判定
	if (abs(halfway_point.x - player->GetLocation().x) <= MAP_CHIP_SIZE
		&& abs(halfway_point.y - player->GetLocation().y) <= MAP_CHIP_SIZE) {
		is_halfway_point = true;
	}


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
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;

		m->Update();
	}




	// カメラワークが固定されたらボス部屋を閉める
	if (camera_work != nullptr) {
		if (camera_work->GetCameraState() == CameraWork::STATE::FIXED &&
			player->GetLocation().x > SCREEN_WIDTH
			) {
			if (false == camera_work->GetCameraLock()) {
				camera_work->SetCameraLock(true);
				
				for (int i = 0; i < 17; i++) {
					AddFixedMapChip(25, 386, i);
				}
			}
			
		}
	}

#ifdef _STAGE_BUILDER
	stage_builder->Update();
#endif

	element->Update(player);

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
	}

#ifdef _STAGE_BUILDER
	stage_builder->Draw();
#endif

	element->Draw();
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


/// <summary>
/// ステージの初期化
/// </summary>
void Stage::InitStage(void)
{

	//マップチップの描画情報をセット
	for (float y = 0; y < map_data.size(); y++)
	{
		for (float x = 0; x < map_data.at(0).size(); x++)
		{
			short i = map_data.at(y).at(x);
			if (i != 0 && i != -1)
			{
				//スポーン地点ID
				const short spawn_point_id = 777;
				if (i == spawn_point_id) {
					spawn_point = { x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
						y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
					};
					continue;
				}

				//中間地点ID
				const short halfway_point_id = 100;
				if (i == halfway_point_id) {
					halfway_point = { x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
						y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
					};
					continue;
				}

				//エネミーのidの場合は、enemy_init_locationにPushしてスキップ
				if (enemy_id.find(i) != enemy_id.end()) {
					enemy_init_location.push_back({ i,
							x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
							y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
						});
					continue;
				}

				if (element->GetElementID().find(i) != element->GetElementID().end()) {

					element->AddElement(i, {
						x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
						y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
						}, { CHIP_SIZE,CHIP_SIZE });
				}
				else {
					// 固定ブロックの追加
					AddFixedMapChip(i, x, y);

				}
			}


		}
	}

}

void Stage::AddFixedMapChip(short id, float x, float y)
{
	if (stage_id_base.find(id) != stage_id_base.end()) {
		int rand = GetRand(4);
		rand += 5;
		mapchip.push_back(new MapChip
		(&stage1_block_images[rand],
			{
				x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
				y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
			}, { CHIP_SIZE,CHIP_SIZE }));
	}

	else if (stage_id_underground.find(id) != stage_id_underground.end()) {
		int rand = GetRand(4);
		mapchip.push_back(new MapChip
		(&stage1_block_images[rand],
			{
				x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
				y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
			}, { CHIP_SIZE,CHIP_SIZE }));
	}

	//固定マップチップ
	else if (id < 50) {
		mapchip.push_back(new MapChip
		(&block_images[id],
			{
				x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
				y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
			}, { CHIP_SIZE,CHIP_SIZE }));
	}

}

std::vector<MapChip*> Stage::GetMapChip() const
{

	std::vector<MapChip*>map_chip = mapchip;
	std::vector<Stage_Element_Base*>e_map_chip = GetElement_MapChip();
	map_chip.insert(map_chip.end(), e_map_chip.begin(), e_map_chip.end());
	return map_chip;
}

std::vector<Stage_Element_Base*> Stage::GetElement_MapChip() const
{

	return	element->GetMapChip();
}