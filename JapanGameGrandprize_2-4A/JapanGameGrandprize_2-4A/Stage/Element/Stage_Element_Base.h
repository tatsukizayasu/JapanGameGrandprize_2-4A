#pragma once
#include "../Define.h"

class Player;
class MapChip;

class Stage_Element_Base
{
private:


protected:
	
	MapChip* mapchip;
	int image;
	

public:
	
	//デフォルトコンストラクタ
	Stage_Element_Base();

	//コンストラクタ
	Stage_Element_Base(MapChip* mapchip, int image);
	//コンストラクタ
	//Stage_Element(const int* p_image, Location location, Area area);
	//デストラクタ
	~Stage_Element_Base();
	//更新
	virtual void Update(Player* player) = 0;
	//描画
	virtual void Draw() const = 0;

	/// <summary>
	/// プレイヤーとブロックが当たっているかのGetter
	/// </summary>
	bool HitPlayer(Player* player) const;
};