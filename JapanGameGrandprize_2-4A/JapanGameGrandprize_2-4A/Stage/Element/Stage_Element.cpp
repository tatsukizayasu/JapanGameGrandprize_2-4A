#include "Stage_Element.h"
#include "../CameraWork.h"

//#define NODEBUG

Stage_Element::Stage_Element()
{

	player = nullptr;
}

Stage_Element::~Stage_Element()
{

	// 読み込んだ全Elementの画像を解放
	for (const auto& entry : image_cache)
	{
		for (auto& value : entry.second)
		{
			DeleteGraph(value);
		}
	}

	// element Vectorを解放
	// 各インスタンスは自動的に解放される。
	element.clear();
	element.shrink_to_fit();
}

void Stage_Element::AddElement(short type, Location location, Area area)
{

#ifndef NODEBUG

	std::vector<int> images = GetImage(type);
	/*int* images = new int[buf.size()];
	std::copy(buf.begin(), buf.end(), images);*/

	switch (type)
	{
	case DAMAGE_WALL:
		element.push_back(std::make_shared<Element_DamageWall>(type, element, images, location, Area{ -MAP_CHIP_SIZE, -MAP_CHIP_SIZE }));
		break;

	case WOODEN_FLOOR:
		element.push_back(std::make_shared <Element_Wooden_Floor>(type, element, images, location, Area{ 10.0f, MAP_CHIP_SIZE }));
		break;

	case FALL_FLOOR:
		element.push_back(std::make_shared<Element_Fall_Floor>(type, element, images, location, Area{ 10.0f , MAP_CHIP_SIZE }));
		break;

	case ITEM_DROP_OBJECT:
		element.push_back(std::make_shared<Element_Item_Drop_Object>(type, element, images, Location{ location.x, location.y - 16.0f }, Area{ 50.0f , MAP_CHIP_SIZE }));
		break;

	case TRAP:
		element.push_back(std::make_shared<Element_Trap>(type, element, images, Location{ location.x, location.y - 16.0f }, Area{ 50.0f , MAP_CHIP_SIZE }));
		break;

	case MOVE_FLOOR:
		element.push_back(std::make_shared<Element_Move_Floor>(type, element, images, location, area));
		break;

	case MOVE_FLOOR_GOAL:
		element.push_back(std::make_shared<Element_Move_Floor>(type, location));
		break;


	case BARRICADE_CENTER:
		element.push_back(std::make_shared<Element_Barricade>(type, element, images, location, area));
		break;

	default:
		break;
	}
#endif // !NODEBUG	
}

void Stage_Element::SetElementParameter()
{

	for (auto& m : element)
	{

		for (int i = 1; i < element.size(); i++) {

			if (Element::BARRICADE_CENTER == m->GetType()) {
				auto y = element.at(i);
				

				std::shared_ptr<Element_Barricade> result = std::dynamic_pointer_cast<Element_Barricade>(y);


				if (m.get() == y.get()) {
					result->SetDirection(Element_Barricade::DIRECTION::NONE);
					continue;

				}
				

				//y = static_cast<Element_Barricade>(y);
				//shared_ptr<Element_Barricade> dynamic_pointer_cast(const std::shared_ptr<Stage_Element_Base> &y) noexcept;
				//std::shared_ptr<Element_Barricade> result = std::dynamic_pointer_cast<Element_Barricade>(y);



				if (abs(y->GetLocation().x - m->GetLocation().x) <= MAP_CHIP_SIZE &&
					abs(y->GetLocation().y - m->GetLocation().y) <= MAP_CHIP_SIZE)
				{
					if (y->GetLocation().y < m->GetLocation().y)
					{
						result->SetDirection(Element_Barricade::DIRECTION::UP);
					}
					else if (y->GetLocation().y > m->GetLocation().y)
					{
						result->SetDirection(Element_Barricade::DIRECTION::DOWN);
					}
					else if (y->GetLocation().x < m->GetLocation().x && y->GetLocation().x > m->GetLocation().x ||
						y->GetLocation().y < m->GetLocation().y && y->GetLocation().y > m->GetLocation().y)
					{
						result->SetDirection(Element_Barricade::DIRECTION::CENTER);
					}
					else
					{
						result->SetDirection(Element_Barricade::DIRECTION::NONE);
					}
				}
			}
		}
	}


	//for (auto& m : element)
	//{

	//	for (int i = 1; i < element.size(); i++) {

	//		if (BARRICADE == m->GetType()) {	
	//			auto y = element.at(i);

	//			std::shared_ptr<Element_Barricade> result = std::dynamic_pointer_cast<Element_Barricade>(y);


	//			if (m.get() == y.get()) {
	//				result->SetDirection(Element_Barricade::DIRECTION::NONE);
	//				continue;

	//			}

	//			//y = static_cast<Element_Barricade>(y);
	//			//shared_ptr<Element_Barricade> dynamic_pointer_cast(const std::shared_ptr<Stage_Element_Base> &y) noexcept;
	//			//std::shared_ptr<Element_Barricade> result = std::dynamic_pointer_cast<Element_Barricade>(y);



	//			if (abs(y->GetLocation().x - m->GetLocation().x) <= MAP_CHIP_SIZE &&
	//				abs(y->GetLocation().y - m->GetLocation().y) <= MAP_CHIP_SIZE)
	//			{
	//				if (y->GetLocation().x < m->GetLocation().x)
	//				{
	//					result->SetDirection(Element_Barricade::DIRECTION::LEFT);
	//				}
	//				else if (y->GetLocation().x > m->GetLocation().x)
	//				{
	//					result->SetDirection(Element_Barricade::DIRECTION::RIGHT);
	//				}
	//				else if (y->GetLocation().y < m->GetLocation().y)
	//				{
	//					result->SetDirection(Element_Barricade::DIRECTION::UP);
	//				}
	//				else if (y->GetLocation().y > m->GetLocation().y)
	//				{
	//					result->SetDirection(Element_Barricade::DIRECTION::DOWN);
	//				}
	//				else if (y->GetLocation().x < m->GetLocation().x && y->GetLocation().x > m->GetLocation().x ||
	//					y->GetLocation().y < m->GetLocation().y && y->GetLocation().y > m->GetLocation().y)
	//				{
	//					result->SetDirection(Element_Barricade::DIRECTION::CENTER);
	//				}
	//				else
	//				{
	//					result->SetDirection(Element_Barricade::DIRECTION::NONE);
	//				}
	//			}
	//		}
	//	}
	//}


	//動く床の目標位置の設定
	SetMoveFloorNextLocation();
}

void Stage_Element::SetMoveFloorNextLocation()
{
	int element_size = element.size();
	for (int i = 0; i < element_size; i++)
	{
		if (element.at(i)->GetType() == Element::MOVE_FLOOR)
		{
			for (int j = i + 1; j < element_size; j++)
			{
				if (element.at(j)->GetType() == Element::MOVE_FLOOR_GOAL && element.at(i)->GetLocation().x < element.at(j)->GetLocation().x)
				{
					element.at(i)->SetLocation(element.at(j)->GetLocation());
					i = j + 1;
					break;
				}
			}
		}
	}
}

void Stage_Element::Update(Player* player)
{

	//当たり判定演算範囲
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& e : element)
	{
		if (e == nullptr) continue;

		float x = e->GetLocation().x;
		float y = e->GetLocation().y;
		float w = e->GetArea().width;
		float h = e->GetArea().height;

		//ブロックの範囲を固定化
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// 画面内にあるMapChipオブジェクトだけUpdateする
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;

		e->Update(player);

		//TNTまたはアイテムドロップオブジェクトが壊れた際、nullptrを格納
		if (e->GetType() == Element::TRAP || e->GetType() == Element::ITEM_DROP_OBJECT)
		{
			if (e->GetArea().height < 0 && e->GetArea().width < 0)
			{
				e = nullptr;
			}
		}
	}
}

void Stage_Element::Draw() const
{

	//当たり判定演算範囲
	struct DrawArea
	{
		float width;
		float height;
	} draw;

	draw = { SCREEN_WIDTH + CHIP_SIZE,SCREEN_HEIGHT + CHIP_SIZE };

	Location camera = CameraWork::GetCamera();

	for (auto& e : element)
	{
		if (e == nullptr) continue;

		float x = e->GetLocation().x;
		float y = e->GetLocation().y;
		float w = e->GetArea().width;
		float h = e->GetArea().height;

		//ブロックの範囲を固定化
		w = MAP_CHIP_SIZE;
		h = MAP_CHIP_SIZE;

		// 画面内にあるMapChipオブジェクトだけUpdateする
		if (x + w < camera.x || camera.x + draw.width < x ||
			y + h < camera.y || camera.y + draw.height < y) continue;

		e->Draw();
	}
}

std::vector<int> Stage_Element::GetImage(short type)
{

	// すでに読み込まれた画像がキャッシュにあるかどうかを確認
	if (image_cache.find(type) != image_cache.end()) {

		return image_cache[type];
	}

	// 画像がキャッシュにない場合、読み込みを行う

	std::string filename = "";

	switch (type)
	{
	case DAMAGE_WALL:
		filename = "DamageWall.png";
		break;

	case WOODEN_FLOOR:
		filename = "Wooden_Floor.png";
		break;

	case FALL_FLOOR:
		filename = "Fall_Floor.png";
		break;

	case ITEM_DROP_OBJECT:
		filename = "TRAP.png";
		break;

	case TRAP:
		filename = "TRAP.png";
		break;

	case MOVE_FLOOR:
		filename = "Move_Floor.png";
		break;
	case MOVE_FLOOR_GOAL:
		filename = "DamageWall.png";
		break;

	case BARRICADE_CENTER:
		filename = "Wooden_Floor.png";
		break;

	default:
		filename = "File name not found";
		break;
	}

	// 読み込んだ画像をキャッシュに保存
	image_cache[type] = LoadImage(filename);

	return image_cache[type];
}

std::vector<int> Stage_Element::LoadImage(const std::string& filename)
{

	//デフォルトディレクトリ
	const std::string default_dir = "Images/Stage/Element/";

	const std::string file_dir = default_dir + filename;

	std::vector<int> images;

	int buf = LoadGraph(TEXT(file_dir.c_str()));

	int image_width, image_height;

	GetGraphSize(buf, &image_width, &image_height);

	if (image_width == MAP_CHIP_SIZE && image_height == MAP_CHIP_SIZE)
	{
		images.push_back(buf);
	}
	else
	{
		DeleteGraph(buf);

		int x_num = image_width / MAP_CHIP_SIZE;
		int y_num = image_height / MAP_CHIP_SIZE;
		int total_num = x_num * y_num;

		std::vector<int> buf_images(total_num);

		LoadDivGraph(TEXT(file_dir.c_str()), total_num, x_num, y_num, MAP_CHIP_SIZE, MAP_CHIP_SIZE, &buf_images[0]);

		//要素数を変更し、コピー
		images.resize(total_num);
		std::copy(buf_images.begin(), buf_images.end(), images.begin());
	}

#if 0
	//読み込みログ
	for (int i = 0; i < images.size(); i++) {
		printfDx("[%d]ID:%d\t%s\n", i, images.at(i), TEXT(filename.c_str()));
	}
#endif // 0

	return images;

	//return std::vector<int>();
}