#pragma once
#include <vector>

class ItemBase;

class ItemManeger
{
private:
    std::vector<ItemBase*> m_items;
    int TotalAmount;

public:
	ItemManeger();
	~ItemManeger();

    void AddItem(ItemBase* item);    // アイテムを追加
    int GetItemCount() const;        // 所持数取得
    ItemBase* GetItem(int index);    // アイテム取得
    void RemoveItem(int index);
    void RemoveItemByPointer(ItemBase* target);

    //合計金額の設定
    void SetTotalAmount(int total) { TotalAmount = total; }

    //合計金額の取得
    int GetTotalAmount()const { return TotalAmount; }

};

