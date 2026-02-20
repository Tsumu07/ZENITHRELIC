#pragma once
#include "../Haeder/Object.h"
#include "../Haeder/ItemBase.h"

class ItemDrop : public Object
{
private:
    // このドロップが持つアイテム（所有権あり）
    ItemBase* itemData; 

    int modelHandle;

public:
    // コンストラクタは itemData の所有権を受け取る（nullptr を許す）
    ItemDrop(ItemBase* data);
    ~ItemDrop();

    void Initaliza() override;
    void Update() override;
    void Draw() override;
    void Finaliza() override;
};
