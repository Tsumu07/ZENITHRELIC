#include "../Haeder/EquippedItems.h"
#include "../Haeder/ItemBase.h"
#include "../Haeder/Player.h"

EquippedItems::EquippedItems()
{
    m_slots[0] = nullptr;
    m_slots[1] = nullptr;
}

void EquippedItems::SetItemToSlot(int slot, ItemBase* item)
{
    //境界チェック（ここで不正なindexを完全に遮断する）
    if (slot < 0 || slot >= 2)
    {
        return;
    }

    //nullチェック（アイテムが空ならそのスロットを空にして終了）
    if (item == nullptr)
    {
        m_slots[slot] = nullptr;
        return;
    }

    //重複装備の解除（トグル処理）
    if (m_slots[slot] == item)
    {
        m_slots[slot] = nullptr;
        return;
    }

    //他のスロットに同じアイテムがあれば外す
    for (int i = 0; i < 2; i++)
    {
        if (m_slots[i] == item)
        {
            m_slots[i] = nullptr;
        }
    }

    // セット
    m_slots[slot] = item;
}

ItemBase* EquippedItems::GetItem(int slot)
{
    if (slot < 0 || slot >= 2)
    {
        return nullptr;
    }

    return m_slots[slot];
}

void EquippedItems::Use(int slot, Player* player)
{
    if (slot < 0 || slot >= 2)
    {
        return;
    }

    if (m_slots[slot] == nullptr)
    {
        return;
    }

    // アイテム効果発動
    m_slots[slot]->UseItem(player);

}

void EquippedItems::ClearSlot(int slot)
{
    if (slot < 0 || slot >= 2) return;
    m_slots[slot] = nullptr;
}
