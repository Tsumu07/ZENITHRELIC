#include "../Haeder/HitCapsule.h"
#include "../Haeder/Player.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/StageFrame.h"
#include "../Haeder/Wall.h"
#include "../Haeder/ObujectManager.h"
#include "../Master.h"

bool Capsule::CheckCapsuleToHitCapsule(
    VECTOR centerPosition1,
    VECTOR centerPosition2,
    float Cap1R,
    VECTOR centerPosition3,
    VECTOR centerPosition4,
    float Cap2R)

{
    return HitCheck_Capsule_Capsule(centerPosition1, centerPosition2, Cap1R, centerPosition3, centerPosition4, Cap2R);
}

bool Capsule::CheckColliisonToHitCapsule(
    VECTOR SphereCenterPos,
    float  SphereR,
    VECTOR CapPos1,
    VECTOR CapPos2,
    float  CapR)
{
    return HitCheck_Sphere_Capsule(SphereCenterPos, SphereR, CapPos1, CapPos2, CapR);
}

bool Capsule::ResolveWallCollision(float radius, float height,int stageFrameTag, int wallTag, VECTOR& pos, VECTOR& moveVec)
{

    VECTOR capStart = VAdd(pos, VGet(0.0f, -height * 0.5f, 0.0f));
    VECTOR capEnd = VAdd(pos, VGet(0.0f, height * 0.5f, 0.0f));

    VECTOR nextCapStart = VAdd(capStart, moveVec);
    VECTOR nextCapEnd = VAdd(capEnd, moveVec);

    CollisionInfo maxHit = { VGet(0,0,0), 0.0f, false };

    //==============================
    // StageFrame
    //==============================
    auto frames = Master::mpObjectManager->FindsByTag(stageFrameTag);

    for (Object* obj : frames)
    {
        StageFrame* stageframe = dynamic_cast<StageFrame*>(obj);

        if (!stageframe)
        {
            continue;
        }

        const auto& v = stageframe->GetVertex();

        bool hitA = HitCheck_Capsule_Triangle(
            nextCapStart, nextCapEnd, radius,
            v[0].pos, v[1].pos, v[2].pos
        );

        bool hitB = HitCheck_Capsule_Triangle(
            nextCapStart, nextCapEnd, radius,
            v[0].pos, v[2].pos, v[3].pos
        );

        if (!hitA && !hitB)
        {
            continue;
        }

        VECTOR normal = v[0].norm;
        VECTOR p2w = VSub(pos, v[0].pos);
        if (VDot(p2w, normal) < 0.0f)
        {
            normal = VScale(normal, -1.0f);
        }

        float overlap = radius - VDot(p2w, normal);

        if (overlap > maxHit.overlap)
        {
            maxHit = { normal, overlap, true };
        }
    }

    //==============================
    // Wall
    //==============================
    auto walls = Master::mpObjectManager->FindsByTag(wallTag);

    for (Object* obj : walls)
    {
        Wall* wall = dynamic_cast<Wall*>(obj);
        
        if (!wall)
        {
            continue;
        }

        const auto& tris = wall->GetTriangles();

        for (size_t i = 0; i + 2 < tris.size(); i += 3)
        {
            VECTOR p0 = tris[i + 0].pos;
            VECTOR p1 = tris[i + 1].pos;
            VECTOR p2 = tris[i + 2].pos;

            if (!HitCheck_Capsule_Triangle(
                nextCapStart, nextCapEnd, radius,
                p0, p1, p2
            ))
            {
                continue;
            }

            VECTOR normal = VNorm(VCross(VSub(p1, p0), VSub(p2, p0)));
            VECTOR p2w = VSub(pos, p0);
            if (VDot(p2w, normal) < 0.0f)
            {
                normal = VScale(normal, -1.0f);
            }

            float overlap = radius - VDot(p2w, normal);

            if (overlap > maxHit.overlap)
            {
                maxHit = { normal, overlap, true };
            }
        }
    }

    //==============================
    // Šp‚Ì“–‚½‚è”»’è
    //==============================
    if (!maxHit.isHit)
    {
        return false;
    }

    pos = VAdd(pos, VScale(maxHit.normal, maxHit.overlap));

    float dot = VDot(moveVec, maxHit.normal);
    moveVec = VSub(moveVec, VScale(maxHit.normal, dot));

    return true;
}
