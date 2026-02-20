#include "../Haeder/InventoryScene.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Player.h"
#include "../Haeder/ItemManeger.h"
#include "../Haeder/EquippedItems.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/ItemBase.h"
#include "../Master.h"
#include "Dxlib.h"

//実態
Inventory g_inventory;

Inventory::Inventory()
: SceneBase()
, TriangleLeftX(0.0f)
, TriangleLeftY(0.0f)
, TriangleUnderX(0.0f)
, TriangleUnderY(0.0f)
, TriangleUpX(0.0f)
, TriangleUpY(0.0f)
, MaxUp(0.0f)
, MaxUnder(0.0f)
, cursor(0)
,TotalAmount(0)
,InputJoycon(false)
{
}

Inventory::~Inventory()
{
}

void Inventory::Initaliza()
{
	cursor = 0;

	TotalAmount = 0;

	//一瞬の取得
	InputJoycon = false;

}

void Inventory::Update()
{
	Object* player = Master::mpObjectManager->FindByTag(100);
	auto Play = dynamic_cast<Player*>(player);
	ItemManeger* inv = Play->GetInventory();

	int count = inv->GetItemCount();

	DINPUT_JOYSTATE input;

	//入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	if (input.Y == 0)
	{
		InputJoycon = false;
	}

	// 閉じる
	if (CheckDownController(PAD_INPUT_3) != 0 || CheckDownKey(KEY_INPUT_E))
	{
		Master::mpSceneManager->CloseInventory();
	}

	// カーソル移動
	if (input.Y <= -500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_DOWN))
	{
		cursor++;
		InputJoycon = true;

	}

	if (input.Y >= 500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_UP))
	{
		cursor--;
		InputJoycon = true;

	}

	if (cursor < 0)
	{
		cursor = count - 1;
	}

	if (cursor >= count)
	{
		cursor = 0;
	}

	// アイテムを装備(スロット1)
	if (CheckDownController(PAD_INPUT_6) != 0 || CheckDownKey(KEY_INPUT_Z))
	{
		ItemBase* item = inv->GetItem(cursor);

		if (item)
		{
			Play->GetEquippedItems()->SetItemToSlot(1, item);

			// カーソル補正
			if (cursor >= inv->GetItemCount())
			{
				cursor = inv->GetItemCount() - 1;
			}

		}
	}

	// アイテムを装備(スロット2)
	if (CheckDownController(PAD_INPUT_5) != 0 || CheckDownKey(KEY_INPUT_X))
	{
		ItemBase* item = inv->GetItem(cursor);

		if (item)
		{
			Play->GetEquippedItems()->SetItemToSlot(0, item);

			// カーソル補正
			if (cursor >= inv->GetItemCount())
			{
				cursor = inv->GetItemCount() - 1;
			}

		}
	}

	TotalAmount = 0;

	for (int i = 0; i < inv->GetItemCount(); i++)
	{
		ItemBase* item = inv->GetItem(i);

		TotalAmount += item->GetPrice();

	}

	g_inventory.SetTotalAmount(TotalAmount);
}

void Inventory::Draw()
{
	DrawBox(100, 100, 600, 700, GetColor(255, 255, 255), FALSE);
	DrawString(120, 120, "Inventory", GetColor(255, 255, 0));
	DrawString(220, 120, "ZキーとXキーで装備", GetColor(255, 255, 0));

	Object* player = Master::mpObjectManager->FindByTag(100);
	auto Play = dynamic_cast<Player*>(player);

	ItemManeger* inv = Play->GetInventory();

	for (int i = 0; i < inv->GetItemCount(); i++)
	{		
		ItemBase* item = inv->GetItem(i);

		int y = 170 + i * 40;

		if (cursor == i)
		{
			DrawBox(110, y - 5, 590, y + 35, GetColor(50, 50, 255), TRUE);

			DrawString(800, 600, item->GetExplain().c_str(), GetColor(255, 255, 255));
		}

		DrawString(130, y, item->GetName().c_str(), GetColor(255, 255, 255));
		char price[32];
		sprintf_s(price, " : %d", item->GetPrice());
		DrawString(350, y, price, GetColor(255, 255, 0));

		EquippedItems* equip = Play->GetEquippedItems();

		if (item == equip->GetItem(0) || item == equip->GetItem(1))
		{
			// 装備中マーク（□）
			DrawBox(520, y + 5, 540, y + 25, GetColor(255, 255, 0), FALSE);
		}
	}


	EquippedItems* equip = Play->GetEquippedItems();

	char totalamount[32];
	sprintf_s(totalamount, "合計金額  : %d$", TotalAmount);
	DrawString(100, 710, totalamount, GetColor(255, 255, 255));

	DrawString(100, 750, "E = Close", GetColor(200, 200, 200));
}

void Inventory::Finaliza()
{

}

