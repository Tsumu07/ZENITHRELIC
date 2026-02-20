#pragma once

class ItemBase;
class Player;

class EquippedItems
{
private:
    ItemBase* m_slots[2]; // 2つのスロット

public:
    EquippedItems();

    // スロットにアイテムをセット
    void SetItemToSlot(int slot, ItemBase* item);

    // スロットからアイテム取得
    ItemBase* GetItem(int slot);

    // スロットのアイテムを使用
    void Use(int slot, Player* player);

    // スロットを空にする（外す）
    void ClearSlot(int slot);
};