#pragma once
#include "Element.h"
class Element_Wooden_Floor :
	public Stage_Element
{
protected:
	int image;
	Area image_size;
	float ex_rate;

public:

	//コンストラクタ
	Element_Wooden_Floor();
	//コンストラクタ
	Element_Wooden_Floor(const int* p_image, Location location, Area area);
	//デストラクタ
	~Element_Wooden_Floor();
	//更新

	void Update(Player* player);


	//描画
	virtual void Draw() const;
};

