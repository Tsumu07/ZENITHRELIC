#include "../Header/HitSphere.h"

//----‹…“¯Žm‚Ì“–‚½‚è”»’è----
bool Collision::CheckSphereToSphere(
    VECTOR centerPosition1,
    float radius1,
    VECTOR centerPosition2,
    float radius2)
{
    return HitCheck_Sphere_Sphere(centerPosition1, radius1, centerPosition2, radius2);
}
