#pragma once
#include "../Define.h"
#include <memory>
#include <vector>
#include "../MapChip.h"

class Player;


class Stage_Element_Base : public MapChip
{
private:


protected:

	short type;
	std::vector<std::shared_ptr<Stage_Element_Base>> element;
	MapChip* mapchip;


public:

	//デフォルトコンストラクタ
	Stage_Element_Base();

	//コンストラクタ
	Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//コンストラクタ
	//Stage_Element(const int* p_image, Location location, Area area);
	//デストラクタ
	~Stage_Element_Base();
	//更新
	virtual void Update(Player* player) {};
	////描画
	//virtual void Draw() const {};

	/// <summary>
	/// ステージ要素の種類のGetter
	/// </summary>
	short GetType() const { return type; }

	/// <summary>
	/// MapChipオブジェクトのGetter
	/// </summary>
	MapChip* GetMapChip() const { return mapchip; }

	/// <summary>
	/// プレイヤーとブロックが当たっているかのGetter
	/// </summary>
	bool HitPlayer(Player* player) const;

	/// <summary>
	/// ステージ要素の検索
	/// </summary>1
	std::shared_ptr<Stage_Element_Base> SearchElement(short type);
};