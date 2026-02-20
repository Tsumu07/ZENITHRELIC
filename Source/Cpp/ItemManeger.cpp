#include "../Haeder/ItemManeger.h"
#include "../Haeder/ItemBase.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Player.h"

ItemManeger::ItemManeger()
{
}

ItemManeger::~ItemManeger()
{
    // メモリ解放
    for (auto i : m_items)
    {
        delete i;
    }

    m_items.clear();
}

//アイテムの追加
void ItemManeger::AddItem(ItemBase* item)
{
    m_items.push_back(item);
}

//持っているアイテム数
int ItemManeger::GetItemCount() const
{
    return m_items.size();
}

//アイテムの取得
ItemBase* ItemManeger::GetItem(int index)
{
    if (index < 0 || index >= m_items.size())
    {
        return nullptr;
    }

    return m_items[index];
}

//アイテム表示をなくす(データは保持)
void ItemManeger::RemoveItem(int index)
{
    if (index < 0 || index >= m_items.size())
    {
        return;
    }

    m_items.erase(m_items.begin() + index);
}

//アイテムを消費(データ削除)
void ItemManeger::RemoveItemByPointer(ItemBase* target)
{
    for (int i = 0; i < m_items.size(); i++)
    {
        if (m_items[i] == target)
        {
            RemoveItem(i);
            return;
        }
    }
}
