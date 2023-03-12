#pragma once
#include "../Define.h"
#include <memory>
#include <vector>
#include "../MapChip.h"

class Player;


class Stage_Element_Base : public MapChip
{
protected:
	
	MapChip* mapchip;
	short type;


public:
	
	//デフォルトコンストラクタ
	Stage_Element_Base();

	Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//コンストラクタ
	//Stage_Element(const int* p_image, Location location, Area area);
	//デストラクタ
	~Stage_Element_Base();
	virtual void Update(Player* player) {};
	////描画
	//virtual void Draw() const {};

	/// <summary>
	/// プレイヤーとブロックが当たっているかのGetter
	/// </summary>
	bool HitPlayer(Player* player) const;
};