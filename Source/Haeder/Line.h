#pragma once
#include "DxLib.h"

class Line
{
public:
    static bool CheckLineToSphere(
        VECTOR StartLinePosition,
        VECTOR TerminusLinePosition,
        VECTOR centerPosition,
        float radius
    );

};