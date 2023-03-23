#include "Element_Trap.h"
#include "../Player.h"
#include "../CameraWork.h"

#define TIMER	4.0f

#define ATTACK_RANGE 200.0f

Element_Trap::Element_Trap(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->area = area;
	this->type = type;

	this->images = images;


	state = STATE::NONE;
}

Element_Trap::~Element_Trap()
{
	for (int& image : images) {
		DeleteGraph(image);
	}
}

void Element_Trap::Update(Player* player)
{

	if (state == STATE::EXTINGUISHMENT) { return; }

	BulletBase** player_bullet;
	player_bullet = player->GetBullet();


	//プレイヤーの弾との当たり判定
	for (int j = 0; j < BULLET_MAX; j++)
	{
		if (player_bullet[j] == nullptr) { continue; }


		if (player_bullet[j]->HitBox(this))
		{
			printfDx("a");
			state = STATE::EXPLOSION;

			delete player_bullet[j];
			player_bullet[j] = nullptr;
			player->SortBullet(j);
			j--;
		}

	}


	if (state == STATE::EXPLOSION) {

		std::function<void()> explosion = [&]() {
			if (abs(location.x - player->GetLocation().x) <= ATTACK_RANGE
				&& abs(location.y - player->GetLocation().y) <= ATTACK_RANGE) {
				ENEMY_TYPE fireType = ENEMY_TYPE::FIRE;
				player->HpDamage(AttackResource{ 10, &fireType, 5 });
			}

			SetImage(0);
			SetArea({ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });

			state = STATE::EXTINGUISHMENT;

		};

		LoopTimer(1.0f, &explosion);
	}
}


void Element_Trap::Draw()const
{
	//画像がない又はエラーの場合は描画しない
	if (image == 0) { return; }

	//printfDx("camera_x:%f\tcamera_y:%f\n", CameraWork::GetCamera().x, CameraWork::GetCamera().y);
	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	DrawRotaGraphF(x, y, 1.0f, 0, image, TRUE);


	if (state == STATE::EXPLOSION) {
		float elapsed_time = GetElapsedTime(1.0f) * 255;
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - elapsed_time);
		DrawCircleAA(x, y, ATTACK_RANGE, 30, 0xFFFFFF, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
