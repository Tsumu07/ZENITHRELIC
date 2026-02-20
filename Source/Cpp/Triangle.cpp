#include"../Haeder/Triangle.h"

bool Triangle::CheckSphereToTriangle(
    VECTOR centerPosition1,
    float radius1,
    VECTOR trianglePosition1,
    VECTOR trianglePosition2,
    VECTOR trianglePosition3)
{
    return HitCheck_Sphere_Triangle(centerPosition1, radius1, trianglePosition1, trianglePosition2, trianglePosition3);
}
