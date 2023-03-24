#include "Element_Barricade.h"
#include "../Player.h"

Element_Barricade::Element_Barricade(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
	this->area = area;
	this->type = type;
	margin_area = { -18.0f,0.0f };
	this->images = images;

	for (auto& m : element) {
		if (this == m.get())continue;

		if (GetType() == m->GetType()) {
			if (abs(GetLocation().x - m->GetLocation().x) <= MAP_CHIP_SIZE &&
				abs(GetLocation().y - m->GetLocation().y) <= MAP_CHIP_SIZE) {

				if (GetLocation().x < m->GetLocation().x) {
					direction = DIRECTION::LEFT;
				}
				else if (GetLocation().x > m->GetLocation().x) {
					direction = DIRECTION::RIGHT;
				}
				else if (GetLocation().y < m->GetLocation().y) {
					direction = DIRECTION::UP;
				}
				else if (GetLocation().y > m->GetLocation().y) {
					direction = DIRECTION::DOWN;
				}
				else if(GetLocation().x < m->GetLocation().x && GetLocation().x > m->GetLocation().x ||
					GetLocation().y < m->GetLocation().y && GetLocation().y > m->GetLocation().y){
					direction = DIRECTION::CENTER;
				}
				else {
					direction = DIRECTION::NONE;
				}

			}
		}
	}

}

Element_Barricade::~Element_Barricade()
{
}

void Element_Barricade::Update(Player* player)
{



}
