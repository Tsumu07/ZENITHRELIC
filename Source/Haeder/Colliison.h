#pragma once
#include "DxLib.h"

class Collision
{
public:
    static bool CheckSphereToSphere(
        VECTOR centerPosition1,
        float radius1, 
        VECTOR centerPosition2, 
        float radius2
    );

};