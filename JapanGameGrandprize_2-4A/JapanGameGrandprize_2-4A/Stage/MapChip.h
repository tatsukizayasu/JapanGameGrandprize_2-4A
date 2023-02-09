#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f

class MapChip :
    public BoxCollider
{
private:
    int image;
    Area image_size;
    float ex_rate;
public:
    //コンストラクタ
    MapChip();
    //コンストラクタ
    MapChip(const int* p_image, Location location, Area area);
    //デストラクタ
    ~MapChip();
    //更新
    virtual void Update();
    //描画
    virtual void Draw() const;

protected:

};