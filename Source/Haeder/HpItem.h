#pragma once
#include "../Haeder/ItemBase.h"
#include "DxLib.h"

class HpItem : public ItemBase
{
public:
    HpItem() 
    {
        m_price = 150;
        m_iconHandle = LoadGraph("Assets/Hp_Icon.png");
        m_modelHandle = MV1LoadModel("Resource/bottle_green.x");
        MV1SetScale(m_modelHandle, VGet(30.0f, 30.0f, 30.0f));

    }

    virtual void UseItem(Player* player) override;
    virtual std::string GetName() const override { return "HP Potion"; }
    virtual std::string GetExplain() const override { return "‚½‚¾‚Ì‰ñ•œ–ò"; }
    virtual const char* GetDropModelPath() const override { return "Resource/bottle_green.x"; }
    virtual float GetPickupRadius() const override { return 60.0f; } // ­‚µ‘å‚«‚ß
};
