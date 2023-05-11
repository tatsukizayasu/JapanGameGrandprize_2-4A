#include "Element_Barricade.h"
#include "../Player.h"
#include "../CameraWork.h"
#include "Stage_Element.h"	

Element_Barricade::Element_Barricade(short type, std::vector<int> images, Location location, Area area, Area margin_area, DIRECTION direction) : Stage_Element_Base(&images.at(0), location, area)
{

	this->area = area;
	this->type = type;
	this->margin_area = margin_area;
	this->images = images;
	this->direction = direction;	

	switch (direction)
	{
	case Element_Barricade::DIRECTION::NONE:
		this->angle = 0.0;

		break;
	case Element_Barricade::DIRECTION::UP:
		this->angle = DIRECTION_ANGLE::UP;

		break;
	case Element_Barricade::DIRECTION::DOWN:
		//this->angle = DIRECTION_ANGLE::DOWN;
		for (int i = 10; i < 14; i++) {
			this->images.at(i - 10) = this->images.at(i);
		}

		break;
	case Element_Barricade::DIRECTION::CENTER:
		this->angle = 0.0;
		for (int i = 5; i < 9; i++) {
			this->images.at(i - 5) = this->images.at(i);
		}
		break;
	default:
		break;
	}

}

Element_Barricade::~Element_Barricade()
{

}

void Element_Barricade::Update(Player* player)
{
	LoopImages(images, 0.1f, 4, nullptr);
	
	switch (direction)
	{
	case Element_Barricade::DIRECTION::NONE:
		break;
	case Element_Barricade::DIRECTION::UP:
		if (abs(location.x - player->GetLocation().x) <= MAP_CHIP_SIZE
			&& abs(location.y - player->GetLocation().y) <= MAP_CHIP_SIZE * 4 / 3) {
			ENEMY_TYPE enemyType = ENEMY_TYPE::THUNDER;
			std::function<void()> Attack = [&]() { player->HpDamage(AttackResource{ 10, &enemyType, 5 }); };
			Attack();
		}

		//アニメーション更新
		//LoopImages(images, 1.0f, 5, nullptr);
		break;
	case Element_Barricade::DIRECTION::DOWN:
		if (abs(location.x - player->GetLocation().x) <= MAP_CHIP_SIZE
			&& abs(location.y - player->GetLocation().y) <= MAP_CHIP_SIZE * 4 / 3) {
			ENEMY_TYPE enemyType = ENEMY_TYPE::THUNDER;
			std::function<void()> Attack = [&]() { player->HpDamage(AttackResource{ 10, &enemyType, 5 }); };
			Attack();
		}	

		//アニメーション更新
		//LoopImages(images, 1.0f, 11, nullptr, 5	);
		break;
	case Element_Barricade::DIRECTION::CENTER:
		if (abs(location.x - player->GetLocation().x) <= MAP_CHIP_SIZE
			&& abs(location.y - player->GetLocation().y) <= MAP_CHIP_SIZE) {
			ENEMY_TYPE enemyType = ENEMY_TYPE::THUNDER;
			std::function<void()> Attack = [&]() { player->HpDamage(AttackResource{ 10, &enemyType, 5 }); };
			Attack();
		}

		//アニメーション更新
		//LoopImages(images, 1.0f, 5, nullptr, 6);
		break;
	default:
		break;
	}
}

//void Element_Barricade::Draw()const
//{
//
//	//画像がない又はエラーの場合は描画しない
//	if (images == 0) { return; }
//
//	//printfDx("camera_x:%f\tcamera_y:%f\n", CameraWork::GetCamera().x, CameraWork::GetCamera().y);
//	float x = location.x - CameraWork::GetCamera().x;
//	float y = location.y - CameraWork::GetCamera().y;
//
//	//DrawRotaGraphF(x, y, 1.0f, 0, images, TRUE);
//	//DrawFormatStringF(x, y, 0xFFFFFF, "%d", direction);
//}