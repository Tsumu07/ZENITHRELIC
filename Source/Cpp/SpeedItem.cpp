#include "../Header/SpeedItem.h"
#include "../Header/Player.h"
#include "../Header/ObujectManager.h"
#include "../Header/GameManager.h"
#include "../Header/Object.h"
#include "../Master.h"

SpeedItem::SpeedItem()
:EffectPos(VGet(0.0f, 0.0f, 0.0f))
{
	m_price = 50;
	m_iconHandle = LoadGraph("Assets/SpeedItem.png");
	m_modelHandle = MV1LoadModel("Resource/bottle_red.x");
	MV1SetScale(m_modelHandle, VGet(30.0f, 30.0f, 30.0f));


}

void SpeedItem::UseItem(Player* player)
{
    if (!player)
    {
        return;
    }

    //使用後の処理
    EffectPos = player->GetPos();

    //効果時間と上昇量
    player->StartSpeedUp(300, 10.0f);

    //エフェクト
    Master::mpObjectManager->AddEffect("Effect/SpeedUp.efkefc", "SpeedUp", EffectPos, VGet(0.0f, 0.0f, 0.0f), VGet(20.0f, 20.0f, 20.0f));

    Master::mpObjectManager->UpdateEffect("SpeedUp", EffectPos, VGet(0.0f, 0.0f, 0.0f), VGet(20.0f, 20.0f, 20.0f));

    if (Master::mpObjectManager->GetSoundByTag("SpeedUpSE") == -1)
    {
        Master::mpObjectManager->AddSound("Musics/SpeedUp.mp3", "SpeedUpSE", DX_PLAYTYPE_BACK);
    }

}