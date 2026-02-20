#include "../Haeder/Line.h"

bool Line::CheckLineToSphere(
    VECTOR StartLinePosition,
    VECTOR TerminusLinePosition,
    VECTOR centerPosition,
    float radius)
{
    return HitCheck_Line_Sphere(StartLinePosition, TerminusLinePosition, centerPosition, radius);
}
