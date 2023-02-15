#pragma once
#include "../BoxCollider.h"

#define MAP_CHIP_SIZE 40.f
class Player;

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
    void Update(Player* player);
    //描画
    virtual void Draw() const;

    const char* GetName() { return class_name; }

protected:
    const char* class_name = "default";
    int image;
    Area image_size;
    float ex_rate;
    
};