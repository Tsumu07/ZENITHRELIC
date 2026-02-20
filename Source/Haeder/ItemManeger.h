#pragma once
#include <vector>

class ItemBase;

class ItemManeger
{
private:
    std::vector<ItemBase*> m_items;

public:
	ItemManeger();
	~ItemManeger();

    void AddItem(ItemBase* item);    // アイテムを追加
    int GetItemCount() const;        // 所持数取得
    ItemBase* GetItem(int index);    // アイテム取得
    void RemoveItem(int index);
    void RemoveItemByPointer(ItemBase* target);

};

