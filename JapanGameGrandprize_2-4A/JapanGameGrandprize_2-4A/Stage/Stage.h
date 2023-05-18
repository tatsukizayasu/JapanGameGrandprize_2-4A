#pragma once
#include "MapChip.h"
#include <vector>
#include <Windows.h>
#include "StageBuilder/StageBuilder.h"
#include "Element/Stage_Element_Base.h"
#include <set>


#define CHIP_SIZE	40

class Player;

class EnemyBase;

class CameraWork;

class Stage_Element;

namespace Ground {
	const short STAGE01_BASE = 5;			//Stage1 ����u���b�N
	const short STAGE01_UNDERGROUND = 4;			//Stage1 �n���u���b�N
}

struct ENEMY_LOCATION
{
	short id;
	Location location;
};

class Stage
{
private:

	//�I�u�W�F�N�g�ϐ�
	Player* player;
	Stage_Element* element;
	EnemyBase** enemy;
	CameraWork* camera_work;

#ifdef _STAGE_BUILDER
	StageBuilder* stage_builder;
#endif

	// �I�u�W�F�N�g�̃J�������[�N���W
	Location object_camera_work;

	// �J�������[�N�̋����W
	Location old_camera_work;

	

	//�X�|�[���n�_
	Location spawn_point;

	//���Ԓn�_
	Location halfway_point;

	//���Ԓn�_����������̃t���O
	bool is_halfway_point;

	//�}�b�v�z��f�[�^
	std::vector<std::vector<int>> map_data;

	//MapChip�I�u�W�F�N�g
	std::vector<MapChip*> mapchip;

	//�G�l�~�[�X�|�[���n�_Location�\����
	std::vector<ENEMY_LOCATION> enemy_init_location;

	//�G�l�~�[��ID
	std::set<short> enemy_id{ 200,201,202,203,204,205,206,207,208,209,210 };


	//�w�i�摜
	int background_images;
	int block_images[50];
	int stage1_block_images[10];
	
	int bort_image;

	//�X�e�[�W����u���b�N��ID
	std::set<short> stage_id_base{ Ground::STAGE01_BASE };

	//�X�e�[�W�n���u���b�N��ID
	std::set<short> stage_id_underground{ Ground::STAGE01_UNDERGROUND };

	//�X�e�[�W�̔ԍ�
	short stage_num;

	//�w�i�摜
	int background_image[5];
	//�w�i�摜���W
	Location background_location;
	//�w�i�摜RGB
	int backgraound_image_color[3];
	//�w�i�u�����h�l
	int backgraound_blend;



protected:


public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Stage(short stage_num);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Stage();

	/// <summary>
	/// �X�e�[�W�̍X�V
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// �X�e�[�W�w�i�̍X�V
	/// </summary>
	void UpdateStageBackground(bool is_spawn_boss);

	/// <summary>
	/// �X�e�[�W�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�e�[�W�w�i�̕`��
	/// </summary>
	void DrawStageBackground() const;

	/// <summary>
	/// �I�u�W�F�N�g �`��֐�
	/// </summary>
	void DrawObject() const;

	/// <summary>
	/// �I�u�W�F�N�g �J�������[�N
	/// </summary>
	void ObjectCameraWork(Player* player);

	/// <summary>
	/// �X�e�[�W�̓ǂݍ���
	/// </summary>
	void LoadMap(short stage_num);

	/// <summary>
	/// �X�e�[�W�̏�����
	/// </summary>
	void InitStage(void);

	/// <summary>
	/// �Œ�u���b�N�̒ǉ�
	/// </summary>
	/// <param name = "id">short�^�F�X�e�[�W�u���b�NID</param>
	/// <param name = "x">float�^�F���WX</param>
	/// <param name = "y">float�^�F���WY</param>
	void AddFixedMapChip(short id, float x, float y);

	/// <summary>
	/// �X�|�[���n�_		Getter
	/// </summary>
	Location GetSpawnPoint() { return spawn_point; }

	/// <summary>
	/// ���Ԓn�_		Getter
	/// </summary>
	Location GetHalfwayPoint() { return halfway_point; }

	/// <summary>
	/// ���Ԓn�_����������̃t���O		Getter
	/// </summary>
	bool IsHalfwayPoint() { return is_halfway_point; }

	/// <summary>
	/// Stage�N���X��Player�I�u�W�F�N�g��n��Setter
	/// </summary>
	/// <param name = "*player">Player�I�u�W�F�N�g�|�C���^</param>
	void SetPlayer(Player *player) { this->player = player; }

	/// <summary>
	/// Stage�N���X��Enemy�I�u�W�F�N�g��n��Setter
	/// </summary>
	/// <param name = "*player">Player�I�u�W�F�N�g�|�C���^</param>
	void SetEnemy(EnemyBase** enemy);

	/// <summary>
	/// Stage�N���X��CameraWork�I�u�W�F�N�g��n��Setter
	/// </summary>
	/// <param name = "*camera">CameraWork�I�u�W�F�N�g�|�C���^</param>
	void SetCameraWork(CameraWork* camera) { this->camera_work = camera; }

	/// <summary>
	/// �}�b�v�T�C�Y��Geter
	/// </summary>
	/// <returns>�\���̌^�F�}�b�v�T�C�Y</returns>	
	POINT GetMapSize(void) const
	{ 
		POINT mapsize{ map_data.at(0).size(),map_data.size() }; 
		return mapsize; 
	}

	/// <summary>
	/// �}�b�v�`�b�v�I�u�W�F�N�g��Getter
	/// </summary>
	/// <returns>�x�N�^�[�^(MapChip�I�u�W�F�N�g�^)�FMapChip</returns>	
	/// ���S�v�f�����[�v���Ďg��Ȃ�����
	std::vector<MapChip*> GetMapChip() const;

	/// <summary>
	/// Element�I�u�W�F�N�g��Getter
	/// </summary>
	/// <returns>�x�N�^�[�^(Stage_Element_Base�I�u�W�F�N�g�^)�FStage_Element_Base</returns>	
	/// ���S�v�f�����[�v���Ďg��Ȃ�����
	std::vector<Stage_Element_Base*> GetElement_MapChip() const;
	
	/// <summary>
	///�G�l�~�[�X�|�[��Location�\����	Getter
	///	id��200�ԑ�
	/// </summary>
	/// <returns>�x�N�^�[�^(ENEMY_LOCATION�\���̌^)</returns>	
	std::vector<ENEMY_LOCATION> GetEnemy_SpawnLocation() const { return enemy_init_location; }

	/// <summary>
	/// �G�������g�p�����[�^�ݒ�֐�
	/// </summary>
	void SetElement();
};