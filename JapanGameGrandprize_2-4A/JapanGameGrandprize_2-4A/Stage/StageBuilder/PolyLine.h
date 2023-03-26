#pragma once
#include "../Define.h"
#include "../LineCollider.h"
#include "../SphereCollider.h"
#include <vector>

using namespace std;

class PolyLine 
{
private:

    vector<SphereCollider*>bend_points;   //Ü‚ê
    vector<LineCollider*>lines;          //ü
public:
    PolyLine();
    PolyLine(Location bend_points[], unsigned int size);
    PolyLine(const vector<SphereCollider*>spheres);
    ~PolyLine();

    void Update();
    virtual void Draw()const;

    //SphereCollider‚Æ‚Ì“–‚½‚è”»’è
    virtual bool HitSphere(const class SphereCollider* sphere_collider) const;

    //BoxCollider‚Æ‚Ì“–‚½‚è”»’è
    virtual bool HitBox(const class BoxCollider* box_collider) const;

    //LineCollider‚Æ‚Ì“–‚½‚è”»’è
    virtual bool HitLine(const class LineCollider* line_collider)const;

    //“_‚Ìíœ
    void DeleteBendPoint(int index);

    vector<SphereCollider*> GetPoints()const{return bend_points;}
};