#pragma once
#include "../Header/ItemBase.h"
#include "DxLib.h"

class HpItem : public ItemBase
{
private:

    VECTOR EffectPos;

public:

    HpItem();

    virtual void UseItem(Player* player) override;
    virtual std::string GetName() const override { return "HP Potion"; }
    virtual std::string GetExplain() const override { return "‚½‚¾‚Ì‰ñ•œ–ò"; }
    virtual const char* GetDropModelPath() const override { return "Resource/bottle_green.x"; }
    virtual float GetPickupRadius() const override { return 60.0f; } // ­‚µ‘å‚«‚ß
};