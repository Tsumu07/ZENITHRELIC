#pragma once
#include "DxLib.h"

class Triangle
{
public:
    static bool CheckSphereToTriangle(
        VECTOR centerPosition1,
        float radius1,
        VECTOR trianglePosition1,
        VECTOR trianglePosition2,
        VECTOR trianglePosition3
    );

};