#include "../Header/InventoryScene.h"
#include "../Header/SceneManager.h"
#include "../Header/GameManager.h"
#include "../Header/ObujectManager.h"
#include "../Header/Player.h"
#include "../Header/ItemManager.h"
#include "../Header/EquippedItems.h"
#include "../Header/CheckKey.h"
#include "../Header/ItemBase.h"
#include "../Header/Player_UI.h"
#include "../Master.h"
#include "Dxlib.h"

Inventory::Inventory()
:SceneBase()
,Background(-1)
,MenuBack(-1)
,ItemBack(-1)
,SelectpictureR_Handle(-1)
,SelectpictureL_Handle(-1)
,Slot_Handle(-1)
,MenuUI()
,RetrySelectUI(-1)
,TitleSelectUI(-1)
,ExitSelectUI(-1)
,MenuUIX(0.0f)
,RetryUI(0.0f)
,TitleUI(0.0f)
,ExitUI(0.0f)
,SelectpictureR(0.0f)
,SelectpictureL(0.0f)
,SelectY(0.0f)
,Menu(false)
,CloseMenu(false)
,Down(false)
,Up(false)
,Decide(false)
,Equipment_No0(false)
,Equipment_No1(false)
,InputJoycon(false)
,MaxUp(0.0f)
,MaxUnder(0.0f)
,cursor(-1)
,TotalAmount(-1)
,OpenMenu(false)
,CursorMusic(-1)
,m_explainFontHandle(-1)
{
}

Inventory::~Inventory()
{
}

void Inventory::Initaliza()
{

	cursor = 0;

	TotalAmount = 0;

	Background = Master::mpSceneManager->GetLastGameScreen();

	//一瞬の取得
	InputJoycon = false;

	//フォントの指定
	m_explainFontHandle = CreateFontToHandle("游明朝", 15, 3, DX_FONTTYPE_ANTIALIASING);

	//---画像の読み込み---//
	LoadDivGraph("Assets/GameOverUI.png", 6, 2, 3, 320, 108, MenuUI);
	MenuBack = LoadGraph("Assets/Menu.png");
	ItemBack = LoadGraph("Assets/Item.png");
	SelectpictureR_Handle = LoadGraph("Assets/SelectpictureR.png");
	SelectpictureL_Handle = LoadGraph("Assets/SelectpictureL.png");
	Slot_Handle = LoadGraph("Assets/Slot.png");

	//一番上
	MaxUp = 180.0f;

	//一番下
	MaxUnder = 420.0f;

	MenuUIX = 780.0f;
	RetryUI = 250.0f;
	TitleUI = 370.0f;
	ExitUI = 490.0f;

	SelectpictureL = 640.0f;
	SelectpictureR = 1065.0f;
	SelectY = 180.0f;

	RetrySelectUI = 0;
	TitleSelectUI = 0;
	ExitSelectUI = 0;
	OpenMenu = false;

	CursorMusic = LoadSoundMem("Musics/Button.mp3");

	TotalAmount = Master::mpItemManeger->GetTotalAmount();
}

void Inventory::Update()
{

	Object* player = Master::mpObjectManager->FindByTag(100);
	auto Play = dynamic_cast<Player*>(player);
	ItemManeger* inv = Play->GetInventory();

	int count = inv->GetItemCount();


	//--------------------------------
	// 入力取得
	//--------------------------------
	DINPUT_JOYSTATE input;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	CloseMenu = (CheckDownController(PAD_INPUT_4)|| CheckDownKey(KEY_INPUT_LSHIFT));
	Menu = (CheckDownController(PAD_INPUT_1) || CheckDownKey(KEY_INPUT_F));
	Equipment_No0 = (CheckDownController(PAD_INPUT_6)|| CheckDownKey(KEY_INPUT_Q));
	Equipment_No1 = (CheckDownController(PAD_INPUT_5)|| CheckDownKey(KEY_INPUT_E));
	Decide = (CheckDownController(PAD_INPUT_2) || CheckDownKey(KEY_INPUT_SPACE));
	Down = (input.Y >= 500.0f || CheckDownKey(KEY_INPUT_S));
	Up = (input.Y <= -500.0f || CheckDownKey(KEY_INPUT_W));

	if (input.Y == 0)
	{
		InputJoycon = false;
	}

	//メニュー画面の表示
	if (OpenMenu)
	{

		if (CloseMenu)
		{
			OpenMenu = false;
		}

		if (Decide)
		{
			PlaySoundMem(CursorMusic, DX_PLAYTYPE_BACK);

			//ゲーム画面
			if (SelectY >= 175.0f && SelectY <= 185.0f)
			{
				Master::mpSceneManager->ChangeScene(SceneName::GameScene);
				Master::mpSceneManager->RequestCloseInventory();
				OpenMenu = false;

			}

			//タイトル
			else if (SelectY >= 295.0f && SelectY <= 305.0f)
			{
				Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
				Master::mpSceneManager->RequestCloseInventory();
				OpenMenu = false;
			}

			//終了
			else if (SelectY >= 415.0f && SelectY <= 425.0f)
			{
				Master::mpGameManager->EndGameLoop();

			}

		}

		// カーソル移動
		if (Down && !InputJoycon)
		{
			PlaySoundMem(CursorMusic, DX_PLAYTYPE_BACK);

			SelectY += 120.0f;
			InputJoycon = true;

		}

		if (Up && !InputJoycon)
		{
			PlaySoundMem(CursorMusic, DX_PLAYTYPE_BACK);

			SelectY -= 120.0f;
			InputJoycon = true;

		}

		if (SelectY < MaxUp)
		{
			SelectY = 420.0f;
		}

		if (SelectY > MaxUnder)
		{
			SelectY = 180.0f;
		}

	}

	else
	{
		if (Menu)
		{
			PlaySoundMem(CursorMusic, DX_PLAYTYPE_BACK);

			OpenMenu = true;
		}

		// 閉じる
		if (CloseMenu)
		{
			Master::mpSceneManager->RequestCloseInventory();
			return;
		}

		// カーソル移動
		if (Down && !InputJoycon )
		{
			PlaySoundMem(CursorMusic, DX_PLAYTYPE_BACK);

			cursor++;
			InputJoycon = true;

		}

		if (Up && !InputJoycon)
		{
			PlaySoundMem(CursorMusic, DX_PLAYTYPE_BACK);

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

		// アイテムを装備(スロット0)
		if (Equipment_No0)
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

		// アイテムを装備(スロット1)
		if (Equipment_No1)
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

	}

}

void Inventory::Draw()
{

	if (Background != -1)
	{
		DrawGraph(0, 0, Background, TRUE);
	}

	//メニュー画面
	if (OpenMenu)
	{
		DrawGraph(460, 150, MenuBack, true);

		DrawGraph(SelectpictureR, SelectY, SelectpictureR_Handle, true);

		DrawGraph(SelectpictureL, SelectY - 15, SelectpictureL_Handle, true);

		//UI
		DrawGraph(MenuUIX, RetryUI, MenuUI[0 + RetrySelectUI], true);
		DrawGraph(MenuUIX, TitleUI, MenuUI[2 + TitleSelectUI], true);
		DrawGraph(MenuUIX, ExitUI, MenuUI[4 + ExitSelectUI], true);

	}

	else
	{
		DrawGraph(100, 100, ItemBack, true);

		if (GetJoypadNum())
		{
			DrawStringToHandle(150, 150, "Aでメニュー", GetColor(0, 0, 0), m_explainFontHandle);
		}

		else
		{
			DrawStringToHandle(150, 150, "Fでメニュー", GetColor(0, 0, 0), m_explainFontHandle);
		}

		Object* player = Master::mpObjectManager->FindByTag(100);
		auto Play = dynamic_cast<Player*>(player);

		ItemManeger* inv = Play->GetInventory();

		for (int i = 0; i < inv->GetItemCount(); i++)
		{
			ItemBase* item = inv->GetItem(i);

			int y = 190 + i * 40;

			if (cursor == i)
			{
				DrawBox(140, y - 5, 550, y + 25, GetColor(50, 50, 255), FALSE);

				DrawStringToHandle(150, 800, item->GetExplain().c_str(), GetColor(0, 0, 0), m_explainFontHandle);
			}

			DrawStringToHandle(150, y, item->GetName().c_str(), GetColor(0, 0, 0), m_explainFontHandle);

			char price[32];
			sprintf_s(price, " ： %d$", item->GetPrice());
			DrawStringToHandle(350, y, price, GetColor(0, 0, 0), m_explainFontHandle);

			EquippedItems* equip = Play->GetEquippedItems();

			if (item == equip->GetItem(0))
			{
				// 装備中マーク
				DrawBox(500, y, 520, y + 20, GetColor(50, 50, 255), TRUE);
			}

			if (item == equip->GetItem(1))
			{
				// 装備中マーク
				DrawBox(500, y, 520, y + 20, GetColor(255, 50, 50), TRUE);

			}
		}

		EquippedItems* equip = Play->GetEquippedItems();

		ItemBase* item0 = equip->GetItem(0);
		ItemBase* item1 = equip->GetItem(1);

		DrawGraph(1400, 840, Slot_Handle, true);
		DrawGraph(1600, 840, Slot_Handle, true);

		if (item0)
		{
			DrawGraph(1565, 900, item0->GetIcon(), true);
		}

		if (item1)
		{
			DrawGraph(1765, 900, item1->GetIcon(), true);
		}

		char totalamount[32];
		sprintf_s(totalamount, "合計金額  ： %d$", TotalAmount);

		DrawStringToHandle(150, 850, totalamount, GetColor(0, 0, 0), m_explainFontHandle);
	}
}

void Inventory::Finaliza()
{
	DeleteSoundMem(CursorMusic);
	DeleteFontToHandle(m_explainFontHandle);
	DeleteGraph(Background);
	DeleteGraph(MenuBack);
	DeleteGraph(ItemBack);
	DeleteGraph(SelectpictureR_Handle);
	DeleteGraph(SelectpictureL_Handle);
	DeleteGraph(Slot_Handle);
}