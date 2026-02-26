#include "../Haeder/InventoryScene.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Player.h"
#include "../Haeder/ItemManeger.h"
#include "../Haeder/EquippedItems.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/ItemBase.h"
#include "../Haeder/Player_UI.h"
#include "../Master.h"
#include "Dxlib.h"

//実態
Inventory g_inventory;

Inventory::Inventory()
:SceneBase()
,m_player_ui()
,TriangleLeftX(0.0f)
,TriangleLeftY(0.0f)
,TriangleUnderX(0.0f)
,TriangleUnderY(0.0f)
,TriangleUpX(0.0f)
,TriangleUpY(0.0f)
,MaxUp(0.0f)
,MaxUnder(0.0f)
,cursor(0)
,TotalAmount(0)
,Background(0)
,MenuUI()
,RetrySelectUI(0)
,TitleSelectUI(0)
,ExitSelectUI(0)
,MenuUIX(0.0f)
,RetryUI(0.0f)
,TitleUI(0.0f)
,ExitUI(0.0f)
,SelectpictureR(0.0f)
,SelectpictureL(0.0f)
,SelectY(0.0f)
,InputJoycon(false)
,OpenMenu(false)
{
}

Inventory::~Inventory()
{
}

void Inventory::Initaliza()
{
	//プレイヤーのUI
	{
		m_player_ui = new Player_UI();
		m_player_ui->Initaliza();
		m_player_ui->SetLayer(1);
		m_player_ui->SetTag(10);
		m_player_ui->SetPos(VGet(0.0f, 0.0f, 0.0f));
		m_player_ui->SetDir(VGet(1.0f, 0.0f, 0.0f));
		m_player_ui->SetSpeed(0.0f);
		m_player_ui->SetTeam(1);

	}

	cursor = 0;

	TotalAmount = 0;

	Background = Master::mpSceneManager->GetLastGameScreen();

	//一瞬の取得
	InputJoycon = false;

	//メニュー
	LoadDivGraph("Assets/GameOverUI.png", 6, 2, 3, 320, 108, MenuUI);

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
}

void Inventory::Update()
{
	m_player_ui->Update();

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

	//メニュー画面の表示
	if (/*コントローラー対応 ||*/ CheckDownKey(KEY_INPUT_Q))
	{

		if (!OpenMenu)
		{
			OpenMenu = true;
		}
	}

	if (OpenMenu)
	{

		if (CheckDownController(PAD_INPUT_3) != 0 || CheckDownKey(KEY_INPUT_E))
		{
			OpenMenu = false;
		}

		if (CheckDownController(PAD_INPUT_2) != 0 || CheckDownKey(KEY_INPUT_Q))
		{
			//ゲーム画面
			if (SelectY >= 175.0f && SelectY <= 185.0f)
			{
				Master::mpSceneManager->ChangeScene(SceneName::GameScene);

			}

			//タイトル
			else if (SelectY >= 295.0f && SelectY <= 305.0f)
			{
				Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
			}

			//終了
			else if (SelectY >= 415.0f && SelectY <= 425.0f)
			{
				Master::mpGameManager->EndGameLoop();

			}

		}

		// カーソル移動
		if (input.Y <= -500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_DOWN))
		{
			SelectY += 120.0f;
			InputJoycon = true;

		}

		if (input.Y >= 500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_UP))
		{
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
	}

	//OpenMenuがtrueの時

	g_inventory.SetTotalAmount(TotalAmount);
}

void Inventory::Draw()
{

	if (Background != -1)
	{
		DrawGraph(0, 0, Background, TRUE);
	}

	//UI
	m_player_ui->Draw();

	//メニュー画面
	if (OpenMenu)
	{
		LoadGraphScreen(460, 150, "Assets/Menu.png", true);

		LoadGraphScreen(SelectpictureR, SelectY, "Assets/SelectpictureR.png", true);

		LoadGraphScreen(SelectpictureL, SelectY - 15, "Assets/SelectpictureL.png", true);

		//UI
		DrawGraph(MenuUIX, RetryUI, MenuUI[0 + RetrySelectUI], true);
		DrawGraph(MenuUIX, TitleUI, MenuUI[2 + TitleSelectUI], true);
		DrawGraph(MenuUIX, ExitUI, MenuUI[4 + ExitSelectUI], true);

	}

	else
	{
		LoadGraphScreen(100, 100, "Assets/Item.png", true);

		DrawString(150, 150, "L/Rで装備", GetColor(0, 0, 0));

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

				DrawString(150, 800, item->GetExplain().c_str(), GetColor(0, 0, 0));
			}

			DrawString(150, y, item->GetName().c_str(), GetColor(0, 0, 0));
			char price[32];
			sprintf_s(price, " : %d", item->GetPrice());
			DrawString(350, y, price, GetColor(0, 0, 0));

			EquippedItems* equip = Play->GetEquippedItems();

			if (item == equip->GetItem(0))
			{
				// 装備中マーク
				DrawBox(500, y, 520, y + 20, GetColor(50, 50, 255), TRUE);
			}

			else if (item == equip->GetItem(1))
			{
				// 装備中マーク
				DrawBox(500, y, 520, y + 20, GetColor(255, 50, 50), TRUE);

			}
		}

		EquippedItems* equip = Play->GetEquippedItems();

		char totalamount[32];
		sprintf_s(totalamount, "合計金額  : %d$", TotalAmount);
		DrawString(150, 850, totalamount, GetColor(0, 0, 0));
	}
}

void Inventory::Finaliza()
{

}