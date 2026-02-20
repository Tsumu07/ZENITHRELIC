#include "DxLib.h"
#include "../Haeder/Camera.h"
#include "../Haeder/Player.h"
#include "../Haeder/Object.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ResourceManeger.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Wall.h"
#include "../Haeder/Pathfinding.h"
#include "../Master.h"
#include <math.h>
#include <EffekseerForDXLib.h>

Camera::Camera()
:mfHorizontalAngle(0.0f)
,mfVerticalAngle(0.0f)
,mvPositon(VGet(0.0f, 0.0f, 0.0f))
,mvLookAtPositon(VGet(0.0f, 0.0f, 0.0f))
,mpPlayer(nullptr)
,Pad(0)
,input()
{

}

Camera::~Camera()
{

}

void Camera::Initaliza(Player *player)
{

    mfHorizontalAngle = 0.0f;
    mfVerticalAngle = 20.0f;

    //プレイヤーの情報を保持していく
    mpPlayer = player;

    //カメラの位置と向きを設定
    SetCameraPositionAndTarget_UpVecY
    (
        VGet(0.0f, 100.0f, -200.0f),
        VGet(0.0f, 100.0f, 0.0f)
    );
    //カメラのクリッピング距離を設定　どこまで写すのか
    SetCameraNearFar(100.0f, 150000.0f);

    //背景の色を黒色にする
   SetBackgroundColor(0, 0, 0);

    //Zバッファに書き込む準備
    SetUseZBufferFlag(true);
    SetWriteZBufferFlag(true);

    //コントローラー
    Pad = DX_INPUT_KEY_PAD1;

}

void Camera::Update()
{
    // 入力情報を取得
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    // 回転角度変更処理
    if (input.Rx < 0 || CheckHitKey(KEY_INPUT_A))
    {
        mfHorizontalAngle += 3.0f;
    }

    if (input.Rx > 0 || CheckHitKey(KEY_INPUT_D))
    {
        mfHorizontalAngle -= 3.0f;
    }

    if (input.Ry > 0 || CheckHitKey(KEY_INPUT_W))
    {
        mfVerticalAngle -= 3.0f;
    }

    if (input.Ry < 0 || CheckHitKey(KEY_INPUT_S))
    {
        mfVerticalAngle += 3.0f;
    }

    // 範囲制限
    if (mfHorizontalAngle > 180.0f)
    {
        mfHorizontalAngle -= 360.0f;
    }

    if (mfHorizontalAngle < -180.0f)
    {
        mfHorizontalAngle += 360.0f;
    }

    if (mfVerticalAngle > 80.0f)
    {
        mfVerticalAngle = 80.0f;
    }

    if (mfVerticalAngle < 5.0f)
    {
        mfVerticalAngle = 5.0f; // 少し下限を上げる
    }

    VECTOR tempPosition2 = VGet(0.0f, 0.0f, 0.0f);

    //注視点はキャラクターモデルの座標から少し高い位置にしておく
    mvLookAtPositon = mpPlayer->GetPos();
    mvLookAtPositon.y += 180.0f;

    tempPosition2.x = 250.0f * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * sinf(mfHorizontalAngle / 180.0f * DX_PI_F);
    tempPosition2.y = 250.0f * sin(mfVerticalAngle / 180.0f * DX_PI_F);
    tempPosition2.z = -(250.0f * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * cosf(mfHorizontalAngle / 180.0f * DX_PI_F));

    //プレイヤー基準のオフセット位置
    VECTOR desiredPos = VAdd(tempPosition2, mvLookAtPositon);

    //最終的に決まるカメラ位置
    VECTOR finalPos = desiredPos;

    //最も近い衝突位置
    float nearestT = 1.0f;

    //全オブジェクト取得
    auto& objList = Master::mpObjectManager->GetObjectList();

    //プレイヤーからカメラ方向ベクトル
    VECTOR dir = VSub(desiredPos, mvLookAtPositon);

    //円判定用
    VECTOR dirXZ = dir;
    dirXZ.y = 0;

    //レイがゼロでなければ判定開始
    if (VSize(dir) > 0.0001f)
    {

        for (auto obj : objList)
        {

            // 柱(円判定 XZ)
            if (obj->IsCylinder())
            {
                VECTOR center = obj->GetPos();
                float radius = obj->GetRadius();

                //プレイヤー基準での円の位置
                VECTOR toCenter = VSub(mvLookAtPositon, center);
                toCenter.y = 0;

                //レイ方向
                float rayLengthSquared = VDot(dirXZ, dirXZ);

                //レイと円中心の内積
                float rayDotCenter = 2.0f * VDot(dirXZ, toCenter);

                //中心距離 - 半径2
                float centerDistanceSquared = VDot(toCenter, toCenter) - radius * radius;

                //判別式
                float discriminant = rayDotCenter * rayDotCenter - 4 * rayLengthSquared * centerDistanceSquared;

                //解がある場合のみ衝突
                if (discriminant >= 0.0f)
                {
                    float sqrtDiscriminant = sqrtf(discriminant);

                    float entryTime = (-rayDotCenter - sqrtDiscriminant) / (2 * rayLengthSquared);
                    float exitTime = (-rayDotCenter + sqrtDiscriminant) / (2 * rayLengthSquared);

                    float hitTime = -1.0f;

                    if (entryTime >= 0.0f && entryTime <= 1.0f)
                    {
                        hitTime = entryTime;
                    }

                    else if (exitTime >= 0.0f && exitTime <= 1.0f)
                    {
                        hitTime = exitTime;
                    }

                    //一番近い衝突を記録
                    if (hitTime >= 0.0f && hitTime < nearestT)
                    {
                        nearestT = hitTime;
                    }
                }
            }

            //壁(AABB判定 XZ)
            else
            {
                Wall* wall = dynamic_cast<Wall*>(obj);
                if (!wall)
                {
                    continue;
                }

                WallBox box = wall->GetAABB_XZ();

                // すでに箱の中なら無視
                if (mvLookAtPositon.x > box.minX && mvLookAtPositon.x < box.maxX &&
                    mvLookAtPositon.z > box.minZ && mvLookAtPositon.z < box.maxZ)
                {
                    continue;
                }

                float tMin = 0.0f;
                float tMax = 1.0f;

                // X軸
                if (fabs(dir.x) > 0.0001f)
                {
                    float tx1 = (box.minX - mvLookAtPositon.x) / dir.x;
                    float tx2 = (box.maxX - mvLookAtPositon.x) / dir.x;

                    if (tx1 > tx2)
                    {
                        std::swap(tx1, tx2);
                    }

                    tMin = max(tMin, tx1);
                    tMax = min(tMax, tx2);
                }
                else if (mvLookAtPositon.x < box.minX || mvLookAtPositon.x > box.maxX)
                {
                    continue;
                }

                //Z軸
                if (fabs(dir.z) > 0.0001f)
                {
                    float tz1 = (box.minZ - mvLookAtPositon.z) / dir.z;
                    float tz2 = (box.maxZ - mvLookAtPositon.z) / dir.z;

                    if (tz1 > tz2)
                    {
                        std::swap(tz1, tz2);
                    }

                    tMin = max(tMin, tz1);
                    tMax = min(tMax, tz2);
                }

                else if (mvLookAtPositon.z < box.minZ || mvLookAtPositon.z > box.maxZ)
                {
                    continue;
                }

                if (tMax >= tMin && tMin >= 0.0f && tMin <= 1.0f)
                {
                    if (tMin < nearestT)
                    {
                        nearestT = tMin;
                    }
                }
            }
        }

        // ===== 最終衝突位置 =====
        if (nearestT < 1.0f)
        {
            VECTOR hitPos = VAdd(mvLookAtPositon, VScale(dir, nearestT));
            VECTOR pushDir = dir;
            pushDir.y = 0;

            if (VSize(pushDir) > 0.0001f)
            {
                pushDir = VNorm(pushDir);
                finalPos = VSub(hitPos, VScale(pushDir, 10.0f));
            }
        }
    }

    //カメラ移動処理
    //衝突しているときだけ補間
    static bool wasColliding = false;

    if (nearestT < 1.0f)
    {
        wasColliding = true;

        VECTOR delta = VSub(finalPos, mvPositon);
        mvPositon.x += delta.x * 0.2f;
        mvPositon.z += delta.z * 0.2f;
        mvPositon.y = finalPos.y;
    }

    else
    {
        if (wasColliding)
        {
            // 解除直後だけなめらかに戻す
            VECTOR delta = VSub(desiredPos, mvPositon);
            mvPositon.x += delta.x * 0.2f;
            mvPositon.z += delta.z * 0.2f;
            mvPositon.y = desiredPos.y;

            if (VSize(delta) < 1.0f)
            {
                wasColliding = false;
            }
        }
        else
        {
            mvPositon = desiredPos;
        }
    }

    //カメラの設定に反映する
    SetCameraPositionAndTarget_UpVecY(mvPositon, mvLookAtPositon);

    int cameraCB = Master::mpResourceManager->GetConstBuff("Camera");
    CB_LIGHT_CAMERA* cb = (CB_LIGHT_CAMERA*)GetBufferShaderConstantBuffer(cameraCB);
    cb->CameraPos.x = mvPositon.x;
    cb->CameraPos.y = mvPositon.y;
    cb->CameraPos.z = mvPositon.z;
    cb->CameraPos.w = 1.0f;
    VECTOR lightDir = VNorm(VGet(1.0f, -1.0f, 1.0f));
    cb->LightDir.x = lightDir.x;
    cb->LightDir.y = lightDir.y;
    cb->LightDir.z = lightDir.z;
    cb->LightDir.w = 0.0f;
    UpdateShaderConstantBuffer(cameraCB);

}