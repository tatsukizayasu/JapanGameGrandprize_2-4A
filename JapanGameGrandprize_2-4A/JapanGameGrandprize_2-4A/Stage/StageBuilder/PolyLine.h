#pragma once
#include "../Define.h"
#include "../LineCollider.h"
#include "../SphereCollider.h"
#include <vector>

using namespace std;

class PolyLine 
{
private:

    vector<SphereCollider*>bend_points;   //ê‹ÇÍ
    vector<LineCollider_t*>lines;          //ê¸
public:

    PolyLine(Location bend_points[], unsigned int size);
    PolyLine(const vector<SphereCollider*>spheres);
    ~PolyLine();

    void Update();
    virtual void Draw()const;

    vector<SphereCollider*> GetPoint()const{return bend_points;}
};