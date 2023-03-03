#pragma once
#include "../Stage.h"

class Stage_Element :
    public Stage, public BoxCollider
{
private:


protected:


public:
	//コンストラクタ
	Stage_Element();
	//コンストラクタ
	Stage_Element(const int* p_image, Location location, Area area);
	//デストラクタ
	~Stage_Element();
	//更新
	virtual void Update(Player* player) = 0;
	//描画
	virtual void Draw() const = 0;
};