#include "../Haeder/HpItem.h"
#include "../Haeder/Player.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/Object.h"
#include "../Master.h"

HpItem::HpItem()
:EffectPos(VGet(0.0f,0.0f,0.0f))
{
    
    m_price = 150;
    m_iconHandle = LoadGraph("Assets/Hp_Icon.png");
    m_modelHandle = MV1LoadModel("Resource/bottle_green.x");
    MV1SetScale(m_modelHandle, VGet(30.0f, 30.0f, 30.0f));

}

void HpItem::UseItem(Player* player)
{
    if (!player)
    {
        return;
    }


    EffectPos = player->GetPos();

    player->AddHp(50);
    
    //エフェクト
    if (Master::mpObjectManager->GetEffectByTag("HP") == -1)
    {
        Master::mpObjectManager->AddEffect("Effect/HP.efkefc", "HP", EffectPos, VGet(0.0f, 0.0f, 0.0f), VGet(20.0f, 20.0f, 20.0f));
    }

    Master::mpObjectManager->UpdateEffect("HP", EffectPos, VGet(0.0f, 0.0f, 0.0f), VGet(20.0f, 20.0f, 20.0f));

    if (Master::mpObjectManager->GetSoundByTag("HealSE") == -1)
    {
        Master::mpObjectManager->AddSound("Musics/ステータス治療1.mp3", "HealSE", DX_PLAYTYPE_BACK);
    }

}
