#include "LastBossMagic.h"
#include "CameraWork.h"



//画像枚数
#define MAGIC_IMAGES 10

//スタンバイの時間
#define STANDBY_TIME 60

//アニメーション
#define MAGIC_ANIMATION 3

//魔法の範囲
#define MAGIC_AREA 60

//魔法攻撃のダメージ
#define MAGIC_DAMAGE 10

enum class MAGIC_TYPE 
{
	SLASH = 0,
	THUNDER,
	FIRE,
	DARK
};

//-----------------------------------
//コンストラクタ
//-----------------------------------
LastBossMagic::LastBossMagic()
{
	standby = true;
	can_delete = false;
	Location camera = CameraWork::GetCamera();

	Location spawn_location;
	spawn_location.x = MAGIC_AREA + GetRand(SCREEN_WIDTH - (MAGIC_AREA * 2));
	spawn_location.y = MAGIC_AREA + GetRand(SCREEN_HEIGHT - (MAGIC_AREA * 3));

	location = spawn_location + camera;
	radius = 0;
	angle = 0;
	
	images = nullptr;
	image_num = 0;
	image_size = 0;

	switch (static_cast<MAGIC_TYPE>(GetRand(3)))
	{
	case MAGIC_TYPE::SLASH:
	{
		image_num = MAGIC_IMAGES;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/Slash.png", image_num, 5, 2, 192, 192, images);
		this->type = ENEMY_TYPE::NORMAL;
		image_size = 0.75;
		break;
	}
	case MAGIC_TYPE::THUNDER:
	{
		image_num = MAGIC_IMAGES;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/Thunder.png", image_num, 5, 2, 192, 192, images);
		this->type = ENEMY_TYPE::THUNDER;
		image_size = 0.75;

		break;
	}
	case MAGIC_TYPE::FIRE:
	{
		image_num = MAGIC_IMAGES * 2;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/tktk_Fire_17.png", image_num, 5, 4, 192, 192, images);
		this->type = ENEMY_TYPE::FIRE;
		image_size = 0.8;
		break;
	}
	case MAGIC_TYPE::DARK:
	{
		image_num = MAGIC_IMAGES * 1.5;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/tktk_Darkness_8.png", image_num, 5, 3, 192, 192, images);
		this->type = ENEMY_TYPE::NORMAL;
		image_size = 0.8;
		break;
	}
	default:
		break;
	}

	size = 0.0;
	standby_time = STANDBY_TIME;

	animation = 0;
	argument = 0;
	damage = MAGIC_DAMAGE;
	magic_circle_image = LoadGraph("Images/Enemy/Magic/MagicCircle.png");
}

//-----------------------------------
//コンストラクタ
//-----------------------------------
LastBossMagic::LastBossMagic(const Location spawn_location)
{
	standby = true;
	can_delete = false;

	location = spawn_location;
	radius = 0;
	angle = 0;

	images = nullptr;
	image_num = 0;
	image_size = 0;
	switch (static_cast<MAGIC_TYPE>(GetRand(3)))
	{
	case MAGIC_TYPE::SLASH:
	{
		image_num = MAGIC_IMAGES;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/Slash.png", image_num, 5, 2, 192, 192, images);
		this->type = ENEMY_TYPE::NORMAL;
		image_size = 0.75;
		break;
	}
	case MAGIC_TYPE::THUNDER:
	{
		image_num = MAGIC_IMAGES;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/Thunder.png", image_num, 5, 2, 192, 192, images);
		this->type = ENEMY_TYPE::THUNDER;
		image_size = 0.75;
		break;
	}
	case MAGIC_TYPE::FIRE:
	{
		image_num = MAGIC_IMAGES * 2;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/tktk_Fire_17.png", image_num, 5, 4, 192, 192, images);
		this->type = ENEMY_TYPE::FIRE;
		image_size = 0.8;
		break;
	}
	case MAGIC_TYPE::DARK:
	{
		image_num = MAGIC_IMAGES * 1.5;
		images = new int[image_num];
		LoadDivGraph("Images/Enemy/Magic/tktk_Darkness_8.png", image_num, 5, 3, 192, 192, images);
		this->type = ENEMY_TYPE::NORMAL;
		image_size = 0.8;
		break;
	}
	default:
		break;
	}

	size = 0.0;
	standby_time = STANDBY_TIME;

	animation = 0;
	argument = 0;
	damage = MAGIC_DAMAGE;

	magic_circle_image = LoadGraph("Images/Enemy/Magic/MagicCircle.png");

}

//-----------------------------------
//デストラクタ
//-----------------------------------
LastBossMagic::~LastBossMagic()
{
	for (int i = 0; i < image_num; i++)
	{
		DeleteGraph(images[i]);
	}

	delete[] images;
}

//-----------------------------------
//更新
//-----------------------------------
void LastBossMagic::Update()
{
	if (standby) //スタンバイ中
	{
		standby_time--;
		if (standby_time % MAGIC_ANIMATION == 0)
		{
			if (size < 1.0)
			{
				size += 0.2;
			}
		}
		angle += 2;
		if (standby_time < 0)
		{
			standby = false;
			radius = 0;
			size = 0;
		}
	}
	else
	{
		animation++;
		if (animation % MAGIC_ANIMATION == 0)
		{
			argument++;
			if (size < 1.0)
			{
				size += 0.5;
				radius = MAGIC_AREA * size;
			}
			if (image_num - 1 < argument)
			{
				can_delete = true;
			}
		}
	}
}

//-----------------------------------
//描画
//-----------------------------------
void LastBossMagic::Draw() const
{
	Location draw_location = location;
	Location camera = CameraWork::GetCamera();
	draw_location = draw_location - camera;

	if (standby) //スタンバイ中
	{
		DrawRotaGraphF(draw_location.x, draw_location.y, 0.1 * size, M_PI /180 * angle, magic_circle_image, TRUE);
	}
	else
	{
		DrawRotaGraphF(draw_location.x, draw_location.y, image_size, 0.0, images[argument], TRUE);
	}
}

//-----------------------------------
//削除可能フラグの取得
//-----------------------------------
bool LastBossMagic::GetCanDelete() const
{
	return can_delete;
}

//-----------------------------------
//スタンバイ状態の取得
//-----------------------------------
bool LastBossMagic::GetDoStandby() const
{
	return standby;
}