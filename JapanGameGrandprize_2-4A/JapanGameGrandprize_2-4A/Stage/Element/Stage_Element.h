#pragma once
#include "../Stage/Stage.h"
#include "../Player.h"
#include "../MapChip.h"
#include "Stage_Element_Base.h"
#include "Element_DamageWall.h"
#include "Element_Wooden_Floor.h"
#include <memory>

namespace Element {
	const int DEBUG_GRASS = 1;		//デバック用草ブロック
	const int DEBUG_SOIL = 4;		//デバック用土ブロック
	const int DEBUG_WOOD = 23;		//デバック用木ブロック
	const int GreenButton = 61;		//緑のボタン
	const int YellowButton = 62;	//黄色のボタン
}

class Stage_Element
{
private:

	//オブジェクト変数
	std::vector<std::shared_ptr<Stage_Element_Base>> element;
	Player* player;

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
	/// ステージ要素の作成
	/// </summary>
	void AddElement(MapChip* mapchip, int image, short type);

	/// <summary>
	/// ステージ要素の更新
	/// </summary>
	void Update(Player *player);

	/// <summary>
	/// ステージ要素の描画
	/// </summary>
	void Draw() const;
};