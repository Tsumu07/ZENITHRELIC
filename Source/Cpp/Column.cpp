#include "DxLib.h"
#include "../Haeder/Column.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Object.h"
#include "../Haeder/HpItem.h"
#include "../Haeder/ItemDrop.h"
#include "../Haeder/ItemBase.h"
#include "../Master.h"
#include <math.h>

//コンストラクタ
Column::Column()
    : Object()
    , mnColumnModelHandle(-1)
    , mvColumnPosition(VGet(0.0f, 0.0f, 0.0f))
    , ColumnRotationY(0.0f)
    , DeleteColumnCount(0.0f)
    , ItemRandom(0.0f)
{
}

//デストラクタ
Column::~Column()
{
}

//初期化
void Column::Initaliza()
{
    //モデルの読み込み
    mnColumnModelHandle = MV1LoadModel("Resource/archway_pillar02.x");

    //3Dモデルの大きさ
    MV1SetScale(mnColumnModelHandle, VGet(0.5f, 0.5f, 0.5f));

    ColumnRotationY = 0.0f;

}

//更新
void Column::Update()
{
    MV1SetPosition(mnColumnModelHandle, GetPos());

    if (IsDead())
    {
        // 初回だけタイマーをセット
        if (DeleteColumnCount <= 0.0f)
        {
            DeleteColumnCount = 120.0f;
        }

        // カウントダウン
        if (DeleteColumnCount > 0.0f)
        {
            --DeleteColumnCount;
        }

        // 0になったら削除
        if (DeleteColumnCount <= 0.0f)
        {
            SetDeleteFlag(true);
            DeleteColumnCount = 0.0f;

            // --- アイテム生成 --- //
            ItemRandom = GetRand(0); // 0,1,2のランダム
            ItemBase* itemData = nullptr;

            switch (ItemRandom)
            {
            case 0:
            {
                itemData = new HpItem();
                break;
            }

            case 1:
            {
                // アイテム追加
                break;
            }
            default:
                break;
            }

            ItemDrop* drop = new ItemDrop(itemData);
            drop->SetPos(GetPos());
            drop->Initaliza();
            drop->SetTag(500);

            Master::mpObjectManager->AddObjectList(drop);

        }
    }
}

//描画
void Column::Draw()
{
    MV1DrawModel(mnColumnModelHandle);

}

//終了処理
void Column::Finaliza()
{
    //3Dモデル削除
    MV1DeleteModel(mnColumnModelHandle);

}
