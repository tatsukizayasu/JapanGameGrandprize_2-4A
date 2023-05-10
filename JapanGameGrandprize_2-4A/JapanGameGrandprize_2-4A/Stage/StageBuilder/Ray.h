#pragma once
#include "../../LineCollider.h"
#include <vector>

using namespace std;

//本来始点から一番近いオブジェクトを認識したいところが、
//今回はPolyLine以外に使う予定がないため、当たっているものの中に
//PolyLineが含まれているか判断できれば良しとする

class Ray :
    public LineCollider
{
private:
    std::vector<ColliderBase*>hit_colliders;
    const Location* base_location;
    COLLIDER hit_collider_type;
    Location shift = {};

public:
    Ray();
    Ray(const Location* location, float shift_x = 0, float shift_y = 0);
    ~Ray();

    void Update();
    void Draw()const;

    void UpdateLocation();
    void HitFunction(ColliderBase* collider);

    const ColliderBase* SearchCollider(COLLIDER collider_type)const;
};

