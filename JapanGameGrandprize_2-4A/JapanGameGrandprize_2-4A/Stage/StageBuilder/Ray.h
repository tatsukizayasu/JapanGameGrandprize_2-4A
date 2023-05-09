#pragma once
#include "../../LineCollider.h"
class Ray :
    public LineCollider
{
private:
    const Location* base_location;

public:
    Ray();
    Ray(const Location* location);
    ~Ray();

};

