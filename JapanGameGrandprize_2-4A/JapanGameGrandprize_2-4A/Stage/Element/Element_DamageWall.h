#pragma once

class Player;

class Element_DamageWall
{
private:

	//オブジェクト
	Player* player;

public:

	//コンストラクタ
	Element_DamageWall();
	//デストラクタ
	~Element_DamageWall();
	//更新
	void Update(Player* player);
	//描画
	void Draw() const;


};