#include "Element_Conveyor_Belt.h"
#include "../Player.h"

Element_Conveyor_Belt::Element_Conveyor_Belt(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->area = area;
	this->type = type;
	margin_area = { -18.0f,0.0f };
	this->images = images;



}

Element_Conveyor_Belt::~Element_Conveyor_Belt()
{
	for (int& image : images) {
		DeleteGraph(image);
	}
}

void Element_Conveyor_Belt::Update(Player* player)
{

	

}
