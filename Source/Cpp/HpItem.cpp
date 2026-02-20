#include "../Haeder/HpItem.h"
#include "../Haeder/Player.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/Object.h"
#include "../Master.h"

void HpItem::UseItem(Player* player)
{
    Object* playerObj = Master::mpObjectManager->FindByTag(100);
    auto Play = dynamic_cast<Player*>(playerObj);

    Play->AddHp(50);   

    //エフェクト
    if (Master::mpObjectManager->GetEffectByTag("buffx") == -1)
    {
        Master::mpObjectManager->AddEffect("Effect/Light.efkefc", "buffx", Play->GetPos(), VGet(0.0f, 0.0f, 0.0f), VGet(10.0f, 10.0f, 10.0f));
    }

}
