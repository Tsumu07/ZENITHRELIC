#pragma once
#include <string>

class Player;

class ItemBase
{
protected:
    std::string m_name;
    int m_price;
    int m_iconHandle;
    int m_modelHandle;

public:

    ItemBase();

    virtual ~ItemBase();

    // アイテム効果
    virtual void UseItem(Player* player) = 0;

    // 名前（Inventory 表示用）
    virtual std::string GetName() const = 0;

    //説明
    virtual std::string GetExplain() const = 0;

    // モデルパス（ドロップ表示用）
    virtual const char* GetDropModelPath() const = 0;

    //UIの表示
    int GetIcon() const;

    // 半径（拾う時の当たり判定）
    virtual float GetPickupRadius() const;

        //アイテムの値段
    int GetPrice() const;
};