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
#include "../EnemyBase.h"

#define STAGE_NAME	"debugStage";
#define STAGE_NAME	"sample_stage2";
#define STAGE_NAME	"Stage01";
//#define STAGE_NAME  "Stage01_test";
//#define STAGE_NAME "Stage02";

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Stage::Stage(short stage_num)
{
	//�X�e�[�W�ԍ����Z�b�g
	this->stage_num = stage_num;

	element = new Stage_Element(this);
	this->camera_work = camera_work;


	//�w�i�摜�ǂݍ���
	for (int i = 0; i < 3; i++) {
		background_image[i] = 0;

		string dis_stage_graph;
		dis_stage_graph = "Images/Scene/Stage/" + to_string(this->stage_num) + "/BackImage" + to_string(i + 1) + ".png";
		const char* dis_stage_graphc = dis_stage_graph.c_str();
		background_image[i] = LoadGraph(dis_stage_graphc);
		if (background_image[i] == -1) {
			/*background_image[i] = LoadGraph("Images/Scene/Stage/1/BackImage1.png");*/
			background_image[i] = 0;
			if (background_image[i] == -1) {
				throw dis_stage_graph;
			}
		}
	}

	background_image[0] = LoadGraph("Images/Scene/Stage/1/GackGround1.png");
	background_image[1] = LoadGraph("Images/Scene/Stage/1/GackGround2.png");
	background_image[2] = LoadGraph("Images/Scene/Stage/1/GackGround3.png");
	background_image[3] = LoadGraph("Images/Scene/Stage/1/GackGround4.png");
	background_image[4] = LoadGraph("Images/Scene/Stage/1/GackGround5.png");

	for (int& c : backgraound_image_color)
	{
		c = 255;
	}

	backgraound_blend = 220;

	background_location = { 0.0f,0.0f };


	//�X�|�[���n�_�ɏ����l���Z�b�g
	spawn_point = { MAP_CHIP_SIZE / 2, SCREEN_HEIGHT / 2 };

	if (LoadDivGraph("Images/Stage/map_chips.png", 50, 10, 5, CHIP_SIZE, CHIP_SIZE, block_images + 1) == -1)
	{
		throw "Images/Stage/map_chips.png";
	}

	if (LoadDivGraph("Images/Stage/stage1_blocks.png", 10, 5, 2, CHIP_SIZE, CHIP_SIZE, stage1_block_images) == -1)
	{
		throw "Images/Stage/stage1_blocks.png";
	}

	// �I�u�W�F�N�g�摜�̓ǂݍ���
	bort_image = LoadGraph("Images/Scene/Stage/3/Bort.png");
	if (bort_image == -1) {
		throw "Images/Scene/Stage/3/Bort.png";
	}


	//�}�b�v�f�[�^�̓ǂݍ���
	LoadMap(stage_num);

	//�t���O���Z�b�g
	is_halfway_point = false;

#ifdef _STAGE_BUILDER
	stage_builder = new StageBuilder();
#endif
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Stage::~Stage()
{
	// �X�e�[�W�w�i�摜���폜
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(background_image[i]);
	}

	// �}�b�v�`�b�v�摜���폜
	for (int i = 0; i < 50; i++)
	{
		DeleteGraph(block_images[i]);
	}

	//vector�̉��

	// map_data���̊evector�����
	for (auto& inner_vec : map_data) {
		inner_vec.clear();
		inner_vec.shrink_to_fit();
	}

	// map_data���̂����
	map_data.clear();
	map_data.shrink_to_fit();

	// MapChip�I�u�W�F�N�g�����
	for (MapChip* chip : mapchip) {
		delete chip;
	}

	// mapchip���̂����
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
// �X�V
//-----------------------------------
void Stage::Update(Player* player)
{
	ObjectCameraWork(player);

	Location player_location = player->GetLocation();

	//Element��Enemy�I�u�W�F�N�g�|�C���^�z����Z�b�g
	if (enemy != nullptr) { element->SetEnemy(enemy); }

	// ���Ԓn�_�Ƃ̓����蔻��
	if (abs(halfway_point.x - player_location.x) <= MAP_CHIP_SIZE
		&& abs(halfway_point.y - player_location.y) <= MAP_CHIP_SIZE) {
		is_halfway_point = true;
	}


	//�����蔻�艉�Z�͈�
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

		//�u���b�N�͈̔͂��Œ艻
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// ��ʓ��ɂ���MapChip�I�u�W�F�N�g����Update����
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;

		m->Update();
	}




	// �J�������[�N���Œ肳�ꂽ��{�X������߂�
	if (camera_work != nullptr)
	{
		if (camera_work->GetCameraState() == CameraWork::STATE::FIXED &&
			SCREEN_WIDTH < player_location.x)
		{
			if (camera_work->GetCameraLock() == false)
			{
				camera_work->SetCameraLock(true);

				//float p_x = fmodf(player_location.x / MAP_CHIP_SIZE, SCREEN_WIDTH / CHIP_SIZE);
				//float wall_location = player_location.x / CHIP_SIZE - p_x + 2;

				//int map_height = map_data.size();
				//for (int i = 0; i < map_height; i++)
				//{
				//	if (map_data.at(i).at(static_cast<int>(wall_location)) < 1)
				//	{
				//		//��ʒ[�Ƀu���b�N��ݒu
				//		//AddFixedMapChip(25, wall_location, static_cast<float>(i));
				//	}
				//}
			}
		}
	}

#ifdef _STAGE_BUILDER
	stage_builder->Update();
#endif

	element->Update(player);

}

void Stage::UpdateStageBackground(bool is_spawn_boss)
{
	//�X�e�[�W3�ŃN���[�P�����o������Ƃ��w�i��ω�������
	if (stage_num == 3)
	{
		//�u�����h�l��ύX
		if (fmodf(background_location.x, SCREEN_WIDTH) == 0 && 80 < backgraound_blend)
		{
			backgraound_blend -= 1;
		}

		if (is_spawn_boss == true)
		{
			//�`��P�x�ύX
			//Green
			if (100 < backgraound_image_color[1])
			{
				backgraound_image_color[1]--;
			}
			//Blue
			if (200 < backgraound_image_color[2])
			{
				backgraound_image_color[2]--;
			}
		}
	}

	//�w�i�摜�̍X�V
	if (stage_num != 3)
	{
		background_location = CameraWork::GetCamera();
	}//Stage03�̏ꍇ�A�w�i��Ɨ��ɓ�����
	else
	{
		background_location.x += 10.0f;
	}
}

//-----------------------------------
// �`��
//-----------------------------------
void Stage::Draw()
{

	//�}�b�v�`�b�v		�`��

	//�`��͈�
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

		//�u���b�N�͈̔͂��Œ艻
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// ��ʓ��ɂ���MapChip�I�u�W�F�N�g�����`�悷��
		if (x + w < camera.x || camera.x + draw.width < x || y + h < camera.y || camera.y + draw.height < y) continue;

		m->Draw();
	}

#ifdef _STAGE_BUILDER
	stage_builder->Draw();
#endif

	element->Draw();
}

void Stage::DrawStageBackground() const
{
	Location location = { 700,200 };
	switch (stage_num)
	{
	case 1:
		DrawBox(0, 0, 1280, 720, 0xffeeee, true);
		DrawGraphF(-fmodf(background_location.x * 0.2, SCREEN_WIDTH), 0				   - background_location.y * 0.2+100, background_image[4], TRUE);
		DrawGraphF(-fmodf(background_location.x * 0.2, SCREEN_WIDTH) + SCREEN_WIDTH, 0 - background_location.y * 0.2 + 100, background_image[4], TRUE);

		DrawGraphF(-fmodf(background_location.x * 0.3, SCREEN_WIDTH), 0				   - background_location.y * 0.3 + 100, background_image[3], TRUE);
		DrawGraphF(-fmodf(background_location.x * 0.3, SCREEN_WIDTH) + SCREEN_WIDTH, 0 - background_location.y * 0.3 + 100, background_image[3], TRUE);

		DrawGraphF(-fmodf(background_location.x * 0.6, SCREEN_WIDTH), 0				   - background_location.y * 0.4 + 100, background_image[2], TRUE);
		DrawGraphF(-fmodf(background_location.x * 0.6, SCREEN_WIDTH) + SCREEN_WIDTH, 0 - background_location.y * 0.4 + 100, background_image[2], TRUE);

		DrawGraphF(-fmodf(background_location.x * 0.8, SCREEN_WIDTH), 0				   - background_location.y * 0.5 + 100, background_image[1], TRUE);
		DrawGraphF(-fmodf(background_location.x * 0.8, SCREEN_WIDTH) + SCREEN_WIDTH, 0 - background_location.y * 0.5 + 100, background_image[1], TRUE);

		DrawGraphF(-fmodf(background_location.x,       SCREEN_WIDTH), 0				   - background_location.y * 0.7 + 100, background_image[0], TRUE);
		DrawGraphF(-fmodf(background_location.x,       SCREEN_WIDTH) + SCREEN_WIDTH, 0 - background_location.y * 0.7 + 100
			
, background_image[0], TRUE);
		break;
	case 2:

		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2), 0, background_image[0], TRUE);
		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH, 0, background_image[0], TRUE);
		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH * 2, 0, background_image[0], TRUE);

		DrawGraphF(200.0f + object_camera_work.x, 100.0f + object_camera_work.y, background_image[1], TRUE);


		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2), 0, background_image[2], TRUE);
		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH, 0, background_image[2], TRUE);
		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH * 2, 0, background_image[2], TRUE);

		break;
	case 3:
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, backgraound_blend);
		SetDrawBright(backgraound_image_color[0], backgraound_image_color[1], backgraound_image_color[2]);

		DrawGraphF(-fmodf(background_location.x * 0.8f + location.x, SCREEN_WIDTH * 2), 0, background_image[1], TRUE);
		DrawTurnGraphF(-fmodf(background_location.x * 0.8f + location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH, 0, background_image[1], TRUE);
		DrawGraphF(-fmodf(background_location.x * 0.8f + location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH * 2, 0, background_image[1], TRUE);

		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2), 0, background_image[0], TRUE);
		DrawTurnGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH, 0, background_image[0], TRUE);
		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH * 2) + SCREEN_WIDTH * 2, 0, background_image[0], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);
		break;
	case 4:
		break;
	case 5:
		break;

	default:
		DrawGraphF(-fmodf(background_location.x * 0.8, SCREEN_WIDTH), 0, background_image[1], TRUE);
		DrawGraphF(-fmodf(background_location.x * 0.8, SCREEN_WIDTH) + SCREEN_WIDTH, 0, background_image[1], TRUE);

		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH), 0, background_image[0], TRUE);
		DrawGraphF(-fmodf(background_location.x, SCREEN_WIDTH) + SCREEN_WIDTH, 0, background_image[0], TRUE);
		break;
	}
}

void Stage::DrawObject() const
{
	if (stage_num == 3) {

		DrawGraphF(80, 460, bort_image, TRUE);
	}
}

void Stage::ObjectCameraWork(Player* player)
{
	Location now_camera_work = CameraWork::GetCamera();

	if (now_camera_work.x != old_camera_work.x) {
		object_camera_work.x = now_camera_work.x - old_camera_work.x;
	
	}
	if (now_camera_work.y != old_camera_work.y) {
		object_camera_work.y -= now_camera_work.y - old_camera_work.y;
	}



	old_camera_work = CameraWork::GetCamera();
}

//-----------------------------------
// �}�b�v�Ǎ���
//-----------------------------------
void Stage::LoadMap(short stage_num)
{

	//const char* stage_name = STAGE_NAME;

	char buf[37];
	sprintf_s(buf, sizeof(buf), "Data/Map_Data/Stage0%d.csv", stage_num);

	int FileHandle;

	if ((FileHandle = FileRead_open(buf)) == 0)
	{
		exit(1);
	}

	char str[2506];		//��s�̒���
	char* context;
	int i = 0, j = 0;

	while (FileRead_gets(str, sizeof(str), FileHandle) != -1)
	{

		char* tmp = strtok_s(str, ",", &context);

		map_data.push_back(std::vector<int>());

		while (tmp != NULL)
		{
			short chip_num = std::stoi(tmp);
			map_data[i].push_back(static_cast<int>(chip_num));

			//�X�|�[���n�_ID
			const short spawn_point_id = 777;
			if (chip_num == spawn_point_id) {
				spawn_point = { j * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
					i * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
				};
			}

			//���Ԓn�_ID
			const short halfway_point_id = 100;
			if (i == halfway_point_id) {
				halfway_point = { j * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
					i * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
				};
			}

			//�G�l�~�[��id�̏ꍇ�́Aenemy_init_location��Push���ăX�L�b�v
			if (enemy_id.find(chip_num) != enemy_id.end()) {
				enemy_init_location.push_back({ chip_num,
						j * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
						i * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
					});
			}

			tmp = strtok_s(NULL, ",", &context);
			j++;
		}

		j = 0;
		i++;
	}

	FileRead_close(FileHandle);
}


/// <summary>
/// �X�e�[�W�̏�����
/// </summary>
void Stage::InitStage(void)
{

	//�}�b�v�`�b�v�̕`������Z�b�g
	for (float y = 0; y < map_data.size(); y++)
	{
		for (float x = 0; x < map_data.at(0).size(); x++)
		{
			short i = map_data.at(y).at(x);
			if (i != 0 && i != -1)
			{
				if (element->GetElementID().find(i) != element->GetElementID().end()) {

					element->AddElement(i, {
						x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
						y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
						}, { CHIP_SIZE,CHIP_SIZE });
				}
				else {
					// �Œ�u���b�N�̒ǉ�
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

	//�Œ�}�b�v�`�b�v
	else if (id < 50) {
		mapchip.push_back(new MapChip
		(&block_images[id],
			{
				x * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2,
				y * MAP_CHIP_SIZE + MAP_CHIP_SIZE / 2
			}, { CHIP_SIZE,CHIP_SIZE }));
	}

}

void Stage::SetEnemy(EnemyBase** enemy)
{
	this->enemy = enemy;
	this->element->SetEnemy(enemy);
}

std::vector<MapChip*> Stage::GetMapChip() const
{

	std::vector<MapChip*>map_chip = mapchip;
	std::vector<Stage_Element_Base*>e_map_chip = GetElement_MapChip();
	map_chip.insert(map_chip.begin(), e_map_chip.begin(), e_map_chip.end());
	return map_chip;
}

std::vector<Stage_Element_Base*> Stage::GetElement_MapChip() const
{

	return	element->GetMapChip();
}

void Stage::SetElement()
{
	element->SetElementParameter();
}
