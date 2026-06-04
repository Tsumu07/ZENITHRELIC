#include "../Header/AttackItem.h"
#include "../Header/Player.h"
#include "../Header/ObujectManager.h"
#include "../Header/GameManager.h"
#include "../Header/Object.h"
#include "../Master.h"

AttackItem::AttackItem()
:EffectPos(VGet(0.0f, 0.0f, 0.0f))
{

	m_price = 200;
	m_iconHandle = LoadGraph("Assets/AttackItem.png");
	m_modelHandle = MV1LoadModel("Resource/bottle_red.x");
	MV1SetScale(m_modelHandle, VGet(30.0f, 30.0f, 30.0f));

}

void AttackItem::UseItem(Player* player)
{
    if (!player)
    {
        return;
    }

    //使用後の処理
    EffectPos = player->GetPos();

    //効果時間と上昇量
    player->StartAttackUp(240, 100.0f);

    //エフェクト
    Master::GetObjectManager()->AddEffect("Effect/AttackUp.efkefc", "AttackUp", EffectPos, VGet(0.0f, 0.0f, 0.0f), VGet(20.0f, 20.0f, 20.0f));

    Master::GetObjectManager()->UpdateEffect("AttackUp", EffectPos, VGet(0.0f, 0.0f, 0.0f), VGet(20.0f, 20.0f, 20.0f));

    if (Master::GetObjectManager()->GetSoundByTag("AttackUpSE") == -1)
    {
        Master::GetObjectManager()->AddSound("Musics/AttackUp.mp3", "AttackUpSE", DX_PLAYTYPE_BACK);
    }

}
