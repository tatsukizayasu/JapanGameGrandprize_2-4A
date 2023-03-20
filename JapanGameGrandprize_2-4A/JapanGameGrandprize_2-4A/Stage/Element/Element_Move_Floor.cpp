#include "Element_Move_Floor.h"

Element_Move_Floor::Element_Move_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area) : Stage_Element_Base(element, &images.at(0), location, area)
{
    this->type = type;
    this->location = location;
    this->area = area;

    is_move = false;
    is_start_point = false;
    next_location = GetLocation();
    speed_x = 1.0f;
    speed_y = 0.0f;

    for (auto& e : element) {
        if (this == e.get()/* || this->GetType() != e->GetType()*/) { continue; }
        

        if (e->GetLocation().x - this->GetLocation().x > 0) {
            is_move = true;
            is_start_point = true;
            next_location = e->GetLocation();
            break;
        }
    }
}

Element_Move_Floor::~Element_Move_Floor()
{

}

void Element_Move_Floor::Update(Player* player)
{
    if (GetLocation().x == next_location.x) {
        is_move = false;
    }

    if (is_move && GetLocation().x < next_location.x)
    {
        float x = GetLocation().x;
        SetLocation({ x + speed_x , GetLocation().y });
    }

    //if (/*ƒvƒŒƒCƒ„[‚ªã‚É“–‚½‚Á‚Ä‚¢‚éŽž*/)
    //{
    //    player->SetLocation({ player->GetLocation().x + speed_x, player->GetLocation().y });
    //}
}
