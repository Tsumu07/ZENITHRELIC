#include "DxLib.h"
#include "../Haeder/Goal.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Object.h"
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
