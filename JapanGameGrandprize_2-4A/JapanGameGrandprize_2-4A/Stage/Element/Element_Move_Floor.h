#pragma once
#include "Stage_Element_Base.h"
#include <windef.h>
class Element_Move_Floor : public Stage_Element_Base
{
private:
	//true=動く,false=止まる
	bool is_move;
	bool is_start_point;
	//目的位置
	Location next_location;
	//移動速度
	Location speed;
public:
	Element_Move_Floor(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, std::vector<int> images, Location location, Area area);
	~Element_Move_Floor();
	
	//更新
	void Update(Player* player)override;
};

