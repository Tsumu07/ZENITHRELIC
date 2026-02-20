#pragma once
#include <string>

class Player;

class ItemBase
{
protected:
    std::string m_name;
    int m_price;
    int m_iconHandle;
    int m_modelHandle = -1;

public:

    ItemBase() {}

    virtual ~ItemBase() {}

    // アイテム効果
    virtual void UseItem(Player* player) = 0;

    // 名前（Inventory 表示用）
    virtual std::string GetName() const = 0;

    //説明
    virtual std::string GetExplain() const = 0;

    // モデルパス（ドロップ表示用）
    virtual const char* GetDropModelPath() const = 0;

    //装備させるモデル
    int GetModel() const { return m_modelHandle; }

    //UIの表示
    int GetIcon() const { return m_iconHandle; }

    // 半径（拾う時の当たり判定）
    virtual float GetPickupRadius() const { return 80.0f; }

    //アイテムの値段
    int GetPrice() const { return m_price; }
};