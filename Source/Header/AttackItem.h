#pragma once
#include "../Header/ItemBase.h"
#include "DxLib.h"

class AttackItem : public ItemBase
{
private:

	VECTOR EffectPos;

public:

	AttackItem();

    virtual void UseItem(Player* player) override;
    virtual std::string GetName() const override { return "Attack Potion"; }
    virtual std::string GetExplain() const override { return "UŒ‚—ÍƒAƒbƒv"; }
    virtual const char* GetDropModelPath() const override { return "Resource/bottle_red.x"; }
    virtual float GetPickupRadius() const override { return 60.0f; } // ­‚µ‘å‚«‚ß

};