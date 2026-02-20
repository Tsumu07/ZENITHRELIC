#include "../Haeder/Colliison.h"

bool Collision::CheckSphereToSphere(
    VECTOR centerPosition1,
    float radius1,
    VECTOR centerPosition2,
    float radius2)
{
    return HitCheck_Sphere_Sphere(centerPosition1, radius1, centerPosition2, radius2);
}
