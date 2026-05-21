#pragma once
#include "../Header/ItemBase.h"
#include "DxLib.h"

class SpeedItem : public ItemBase
{
private:

	VECTOR EffectPos;
public:

	SpeedItem();


    virtual void UseItem(Player* player) override;
    virtual std::string GetName() const override { return "Speed Potion"; }
    virtual std::string GetExplain() const override { return "スピードアップ"; }
    virtual const char* GetDropModelPath() const override { return "Resource/bottle_blue.x"; }
    virtual float GetPickupRadius() const override { return 60.0f; } // 少し大きめ

};