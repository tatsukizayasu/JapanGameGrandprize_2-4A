#pragma once
#include "../Stage/Stage.h"
#include "../Player.h"
#include "../MapChip.h"
#include "Stage_Element_Base.h"
#include "Element_DamageWall.h"
#include "Element_Wooden_Floor.h"
#include <memory>
#include <set>

namespace Element {
	const short DEBUG_GRASS = 1;		//デバック用草ブロック
	const short DEBUG_SOIL = 4;		//デバック用土ブロック
	const short DEBUG_WOOD = 23;		//デバック用木ブロック
	const short GreenButton = 61;		//緑のボタン
	const short YellowButton = 62;	//黄色のボタン
}


class Stage_Element
{
private:

	//オブジェクト変数
	std::vector<std::shared_ptr<Stage_Element_Base>> element;
	Player* player;

	//ステージ要素のID
	std::set<short> elements_id{ Element::DEBUG_GRASS,Element::DEBUG_SOIL, Element::DEBUG_WOOD, Element::GreenButton, Element::YellowButton };

protected:


public:

	//コンストラクタ
	Stage_Element();

	//デストラクタ
	~Stage_Element();

	/// <summary>
	/// Stage_ElementクラスにPlayerオブジェクトを渡すSetter
	/// </summary>
	/// <param name = "*player">Playerオブジェクトポインタ</param>
	void SetPlayer(Player* player) { this->player = player; }

	/// <summary>
	/// ステージ要素ID		Getter
	/// </summary>
	const std::set<short>& GetElementID() { return elements_id; }

	/// <summary>
	/// ElementオブジェクトのGetter
	/// </summary>
	/// <returns>ベクター型(Stage_Element_Baseオブジェクト型)：Stage_Element_Base</returns>	
	/// ※全要素をループして使わないこと
	std::vector<Stage_Element_Base*> GetMapChip() const {
		std::vector<Stage_Element_Base*> result;
		result.reserve(element.size());
		for (const auto& e : element) {
			result.push_back(e.get());
		}
		return result;

	};

	/// <summary>
	/// ステージ要素の作成
	/// </summary>
	void AddElement(short type, int* image, Location location, Area area);

	/// <summary>
	/// ステージ要素の更新
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// ステージ要素の描画
	/// </summary>
	void Draw() const;
};