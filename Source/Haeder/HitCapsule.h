#pragma once
#include "DxLib.h"

class Capsule
{
public:
    static bool CheckCapsuleToHitCapsule(
        VECTOR centerPosition1,
        VECTOR centerPosition2,
        float Cap1R,
        VECTOR centerPosition3,
        VECTOR centerPosition4,
        float Cap2R
    );

    static bool CheckColliisonToHitCapsule(
        VECTOR SphereCenterPos,
        float  SphereR,
        VECTOR CapPos1,
        VECTOR CapPos2,
        float  CapR
    );

    static bool ResolveWallCollision(
        float radius,
        float height,
        int stageFrameTag,
        int wallTag,
        VECTOR& pos,
        VECTOR& moveVec
    );
};