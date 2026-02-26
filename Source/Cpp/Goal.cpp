#include "DxLib.h"
#include "../Haeder/Goal.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Object.h"
#include "../Master.h"
#include <math.h>

//コンストラクタ
Goal::Goal()
: Object()
, mnGoalModelHandle(-1)
,mvGoalRotation(VGet(0.0f,0.0f,0.0f))
{
}

//デストラクタ
Goal::~Goal()
{
}


//初期化
void Goal::Initaliza()
{
    //モデルの読み込み
    mnGoalModelHandle = MV1LoadModel("Resource/PortalSeven.x");

}

//更新
void Goal::Update()
{

    MV1SetPosition(mnGoalModelHandle, GetPos());

    MV1SetRotationXYZ(mnGoalModelHandle, mvGoalRotation);

    //エフェクト
    if (Master::mpObjectManager->GetEffectByTag("Portal") == -1)
    {
        Master::mpObjectManager->AddEffect("Effect/Portal1.efkefc", "Portal", VGet(GetPos().x, GetPos().y + 140.0f, GetPos().z), VGet(0.0f, 0.0f, 0.0f), VGet(15.0f, 15.0f, 15.0f));
    }

}

//描画
void Goal::Draw()
{
    MV1DrawModel(mnGoalModelHandle);

}

//終了処理
void Goal::Finaliza()
{
    //3Dモデル削除
    MV1DeleteModel(mnGoalModelHandle);

}
