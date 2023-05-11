#include "../MapChip.h"
#include "../Player.h"
#include <windef.h>

Stage_Element_Base::Stage_Element_Base()
{

	type = 0;
	this->mapchip = nullptr;
	this->image = 0;
	type = 0;
	count = 0;
	current_image = 0;
	margin_area = { 0, 0 };
}

Stage_Element_Base::Stage_Element_Base(int* image, Location location, Area area) : MapChip(image, location, area)
{

	type = 0;
	this->mapchip = mapchip;
	start_time = chrono::steady_clock::now();
	count = 0;
	current_image = 0;
}

Stage_Element_Base::~Stage_Element_Base()
{

	images.clear();
	images.shrink_to_fit();
}

void Stage_Element_Base::LoopImages(std::vector<int>& images, float time, int total_images, std::function<void()>* callback, int start_image)
{

	auto end_time = std::chrono::steady_clock::now();
	auto diff = end_time - start_time;
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

	if (elapsed.count() >= time * 1000.0f) {
		start_time = end_time;
		current_image += start_image;
		current_image = (current_image + 1) % total_images;
		this->image = images[current_image];

		if (callback != nullptr) {
			(*callback)();
		}
	}
}

//bool Stage_Element_Base::HitPlayer(Player* player) const
//{
//
//	//補正
//
//	struct Rect
//	{
//		float x;
//		float y;
//		float width;
//		float height;
//	};
//
//	Location p_location = player->GetLocation();
//	Area p_area = player->GetArea();
//
//	const Rect mapchip_rect = { location.x - (area.width / 2), location.y - (area.height / 2), area.width, area.height };
//	const Rect player_rect = { p_location.x - (p_area.width / 2), p_location.y - (p_area.height / 2), p_area.width, p_area.height };
//
//	// プレイヤーとマップチップの間の余白を設定
//	const float margin_x = 1.0f - margin_area.width; 
//	const float margin_y = 1.0f - margin_area.height;
//
//	if ((mapchip_rect.x - margin_x < player_rect.x + player_rect.width) && (player_rect.x < mapchip_rect.x + mapchip_rect.width + margin_x)
//		&& (mapchip_rect.y - margin_y < player_rect.y + player_rect.height) && (player_rect.y < mapchip_rect.y + mapchip_rect.height + margin_y))
//	{
//		return true;
//	}
//	return false;
//
//}

std::tuple<bool, HIT_DIRECTION> Stage_Element_Base::HitPlayer(Player* player) const
{

	struct Rect
	{
		float x;
		float y;
		float width;
		float height;
	};

	Location p_location = player->GetLocation();
	Area p_area = player->GetArea();

	const Rect mapchip_rect = { location.x - (area.width / 2), location.y - (area.height / 2), area.width, area.height };
	const Rect player_rect = { p_location.x - (p_area.width / 2), p_location.y - (p_area.height / 2), p_area.width, p_area.height };

	const float margin_x = 1.0f - margin_area.width;
	const float margin_y = 1.0f - margin_area.height;

	bool is_hit = ((mapchip_rect.x - margin_x < player_rect.x + player_rect.width) && (player_rect.x < mapchip_rect.x + mapchip_rect.width + margin_x)
		&& (mapchip_rect.y - margin_y < player_rect.y + player_rect.height) && (player_rect.y < mapchip_rect.y + mapchip_rect.height + margin_y));

	if (!is_hit)
	{
		return std::make_tuple(false, HIT_DIRECTION::NONE);
	}

	float dx = (player_rect.x + player_rect.width / 2) - (mapchip_rect.x + mapchip_rect.width / 2);
	float dy = (player_rect.y + player_rect.height / 2) - (mapchip_rect.y + mapchip_rect.height / 2);

	float width = (player_rect.width + mapchip_rect.width) / 2;
	float height = (player_rect.height + mapchip_rect.height) / 2;

	float cross_width = width * dy;
	float cross_height = height * dx;

	if (cross_width > cross_height)
	{
		if (cross_width > -cross_height)
		{
			return std::make_tuple(true, HIT_DIRECTION::DOWN);
		}
		else
		{
			return std::make_tuple(true, HIT_DIRECTION::LEFT);
		}
	}
	else
	{
		if (cross_width > -cross_height)
		{
			return std::make_tuple(true, HIT_DIRECTION::RIGHT);
		}
		else
		{
			return std::make_tuple(true, HIT_DIRECTION::UP);
		}
	}
}

void Stage_Element_Base::LoopTimer(float time, std::function<void()>* callback)
{

	auto& start_time = start_time_map[time];
	if (start_time == std::chrono::steady_clock::time_point{}) 
	{
		start_time = std::chrono::steady_clock::now();
	}

	auto end_time = chrono::steady_clock::now();
	auto diff = end_time - start_time;
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(diff);
	//elapsed = chrono::duration_cast<chrono::duration<long long, std::milli>>(diff);

	elapsed_time_map[time] = elapsed.count() / 1000.0f;

	if (elapsed.count() >= time * 1000.0f) {
		start_time = end_time;
		count++;
		//printfDx("count:%d\n", count);

		if (callback != nullptr) {
			(*callback)();
		}
	}
}

float Stage_Element_Base::GetElapsedTime(float time) const
{

	auto it = elapsed_time_map.find(time);
	if (it != elapsed_time_map.end())
	{
		return it->second;
	}
	else 
	{
		// エラー値（time値が見つからない場合）
		return -1.0f; 
	}
}

void Stage_Element_Base::ResetElapsedTime(float time)
{

	auto it = elapsed_time_map.find(time);
	if (it != elapsed_time_map.end()) 
	{
		it->second = 0.0f;
		start_time_map[time] = std::chrono::steady_clock::now();
	}
}

void Stage_Element_Base::SetPan(int SoundHandle, Player* player, Stage_Element_Base* base)
{
	Location player_location = player->GetLocation();
	Location base_location = base->GetLocation();

	
	float result = base_location.x - player_location.x;
	result = fmodf(result, 1280);

	int pan = static_cast<int>(result) % 255;

	//printfDx("%d\n", pan);

	ChangePanSoundMem(pan, SoundHandle);
}

//std::shared_ptr<Stage_Element_Base> Stage_Element_Base::SearchElement(short type)
//{
//	for (auto elem : element) {
//		if (elem != nullptr && elem->GetType() == type) 
//		{
//			//MapChip* mapchip = elem->GetMapChip();
//
//			if (mapchip->GetLocation().y > elem->GetMapChip()->GetLocation().y
//				&& mapchip->GetLocation().x == elem->GetMapChip()->GetLocation().x)
//			{
//				SearchElement(type)->GetMapChip()->SetArea(Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE });
//				SearchElement(type)->GetMapChip()->SetImage(0);
//				printfDx("aa");
//				return elem;
//			}
//		}
//	}
//}