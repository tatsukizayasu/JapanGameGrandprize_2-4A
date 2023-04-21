#pragma once
#include "../Define.h"
#include "../LineCollider.h"
#include "../SphereCollider.h"
#include "../BoxCollider.h"
#include "../../ColliderBase.h"
#include <vector>


using namespace std;
class PolyLine 
    :public ColliderBase
{
private:

    vector<SphereCollider*>bend_points;   //折れ
    vector<LineCollider*>lines;          //線
public:
    PolyLine();
    PolyLine(Location bend_points[], unsigned int size);
    PolyLine(const vector<SphereCollider*>spheres);
    PolyLine(const PolyLine &poly_line);
    ~PolyLine();

    void Update();
    virtual void Draw()const;

    //SphereColliderとの当たり判定
    virtual bool HitSphere(const class SphereCollider* sphere_collider) const;

    //BoxColliderとの当たり判定
    virtual bool HitBox(const class BoxCollider* box_collider) const;

    //LineColliderとの当たり判定
    virtual bool HitLine(const class LineCollider* line_collider)const;

    //PolyLineとの当たり判定
    virtual bool HitPolyLine(const class PolyLine* poly_line)const;

    ColliderBase* Copy()const override { return new PolyLine(*this); }

    bool HitCheck(ColliderBase* collider)const;

    //点の削除
    void DeleteBendPoint(int index);

    //中心座標の計算、再計算
    void MakeLocation();

    vector<SphereCollider*> GetPoints()const{return bend_points;}
    const vector<LineCollider*>*GetLines()const { return &lines; }

    //ゲームプレイ時に当たり判定をとる分には必要のないもの
    //ツール上でマウスとの当たり判定をとるために使用しています
#ifdef _STAGE_BUILDER
private:
    SphereCollider pivot;
    vector<Location> vector_to_line;

    Location old_location;
    vector<Location> vector_to_bend_point;

public:
    SphereCollider* GetPivot() { return &pivot; }
    
#endif

};