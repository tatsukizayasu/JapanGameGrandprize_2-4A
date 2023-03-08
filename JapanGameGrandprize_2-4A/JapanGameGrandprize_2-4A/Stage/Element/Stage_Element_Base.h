#pragma once

class Stage_Element_Base
{
private:


protected:
	const int *image;
	

public:
	
	//コンストラクタ
	Stage_Element_Base();
	//コンストラクタ
	//Stage_Element(const int* p_image, Location location, Area area);
	//デストラクタ
	~Stage_Element_Base();
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Draw() const = 0;
};