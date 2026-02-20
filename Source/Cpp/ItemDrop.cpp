#include "../Haeder/ItemDrop.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ItemManeger.h"
#include "../Haeder/Player.h"
#include "../Master.h"
#include "DxLib.h"

ItemDrop::ItemDrop(ItemBase* data)
: itemData(data)
, modelHandle(-1)
{
}

ItemDrop::~ItemDrop()
{
}

void ItemDrop::Initaliza()
{
    // モデル読み込み
    modelHandle = MV1LoadModel(itemData->GetDropModelPath());

    MV1SetScale(modelHandle, VGet(30.0f, 30.0f, 30.0f));

}

void ItemDrop::Update()
{
    // プレイヤー取得
    Object* playerObj = Master::mpObjectManager->FindByTag(100);
    auto player = dynamic_cast<Player*>(playerObj);

    if (!player)
    {
        return;
    }

    // 当たり判定（Sphere）
    float r = itemData->GetPickupRadius() * 3;
    VECTOR diff = VSub(player->GetPos(), GetPos());
    float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

    if (distSq < r * r && player->GetAnimationState() == Animetion::PickItem)
    {
        // プレイヤーへアイテム追加
        player->GetInventory()->AddItem(itemData);

        // このドロップを削除
        SetDeleteFlag(true);

        return;
    }

    VECTOR pos = GetPos();
    pos.y += sinf(GetNowCount() * 0.01f) * 0.5f;
    SetPos(pos);
}

void ItemDrop::Draw()
{
    if (modelHandle >= 0)
    {
        MV1SetPosition(modelHandle, GetPos());
        MV1DrawModel(modelHandle);
    }
}

void ItemDrop::Finaliza()
{
    if (modelHandle >= 0)
    {
        MV1DeleteModel(modelHandle);
    }
}
