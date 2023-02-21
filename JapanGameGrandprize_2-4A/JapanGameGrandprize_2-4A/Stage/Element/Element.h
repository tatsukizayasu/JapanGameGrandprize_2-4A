#pragma once
#include "../Stage.h"

class Stage_Element :
    public Stage
{
private:

protected:

    //アニメーション用タイマー
    float animation_timer;


public:
    Stage_Element();
    ~Stage_Element();
    virtual void Update() = 0;
    virtual void Draw() const = 0;
};