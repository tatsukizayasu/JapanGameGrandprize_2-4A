#pragma once

class Player;

class Element_Wooden_Floor
{
private:

	//オブジェクト
	Player* player;

public:

	//コンストラクタ
	Element_Wooden_Floor();
	//デストラクタ
	~Element_Wooden_Floor();
	//更新
	void Update(Player* player);
	//描画
	void Draw() const;


};