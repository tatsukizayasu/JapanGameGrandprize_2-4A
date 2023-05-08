#pragma once
#include "Stage_Element_Base.h"
#include <windef.h>

#define MOVE_START_TIME 10

class Element_Move_Floor : public Stage_Element_Base
{
private:
	
	//true=動く,false=止まる
	bool is_move;
	//目的位置
	Location next_location;
	//移動速度
	Location speed;
	//移動開始までの時間
	short move_timer;
	//true=動く床の目的地オブジェクト,false=動く床
	bool is_goal_object;
public:

	//動く床のコンストラクタ
	Element_Move_Floor(short type, std::vector<int> images, Location location, Area area);
	//動く床（目標地点のコンストラクタ)
	Element_Move_Floor(short type, Location location);
	~Element_Move_Floor();
	
	//更新
	void Update(Player* player)override;

	//目標位置の設定
	void SetLocation(Location location)override;
	//void SetNextLocation(Location next_location) { this->next_location = next_location; }
};