#include "Element_Move_Floor.h"

Element_Move_Floor::Element_Move_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area)
{
	this->type = type;
	this->location = location;
	this->area = area;

	is_move = false;
	speed_x = 5.f;
	speed_y = 0.f;
}

Element_Move_Floor::~Element_Move_Floor()
{

}

void Element_Move_Floor::Update(Player* player)
{
	if (is_move)
	{
		location.x += speed_x;
	}
}

void Element_Move_Floor::Draw() const
{
	float x = location.x - area.width / 2;
	float y = location.y - area.height / 2;
	
	DrawBoxAA(x, y, x + area.width, y + area.height, 0xff0000, TRUE);
}
