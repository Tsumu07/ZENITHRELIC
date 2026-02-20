#include "DxLib.h"
#include "../Haeder/Player.h"
#include "../Haeder/Player_UI.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/ResourceManeger.h"
#include "../Haeder/ItemBase.h"
#include "../Haeder/EquippedItems.h"
#include "../Master.h"

Player_UI::Player_UI()
:Object()
,LoadShader(-1)
,Frame(0)
,SlotHandle(-1)
,PlayerHp(0.0f)
,PlayerMaxHp(0.0f)
,PlayerHpOld(0.0f)
,m_vertices()
,m_indices()
,GetPlayer()
{
}

Player_UI::~Player_UI()
{
}

void Player_UI::Initaliza()
{
	GetPlayer = Master::mpObjectManager->FindByTag(100);
	auto player = dynamic_cast<Player*>(GetPlayer);

	//プレイヤーの最大HPを取得
	PlayerMaxHp = player->GetHp();
	PlayerHp = player->GetHp();
	PlayerHpOld = PlayerHp;
	Frame = 0;

	// 左上
	m_vertices[0].pos = VGet(20.0f, 20.0f, 0.0f);
	m_vertices[0].u = 0.0f;
	m_vertices[0].v = 0.0f;
	m_vertices[0].dif = GetColorU8(255, 255, 255, 255);
	m_vertices[0].rhw = 1.0f;

	// 右上
	m_vertices[1].pos = VGet(590.0f, 20.0f, 0.0f);
	m_vertices[1].u = 1.0f;
	m_vertices[1].v = 0.0f;
	m_vertices[1].dif = GetColorU8(255, 255, 255, 255);
	m_vertices[1].rhw = 1.0f;

	// 左下
	m_vertices[2].pos = VGet(20.0f, 50.0f, 0.0f);
	m_vertices[2].u = 0.0f;
	m_vertices[2].v = 1.0f;
	m_vertices[2].dif = GetColorU8(255, 255, 255, 255);
	m_vertices[2].rhw = 1.0f;

	// 右下
	m_vertices[3].pos = VGet(590.0f, 50.0f, 0.0f);
	m_vertices[3].u = 1.0f;
	m_vertices[3].v = 1.0f;
	m_vertices[3].dif = GetColorU8(255, 255, 255, 255);
	m_vertices[3].rhw = 1.0f;

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 1;
	m_indices[4] = 3;
	m_indices[5] = 2;

	//HPゲージ用シェーダー読み込み
	LoadShader = LoadPixelShader("gaugePS.cso");

	SlotHandle = LoadGraph("Assets/Slot.png");

}

void Player_UI::Update()
{
	static int tempold = 0;

	auto player = dynamic_cast<Player*>(GetPlayer);

	if (PlayerHp != player->GetHp())
	{
		tempold = PlayerHp;
		PlayerHp = player->GetHp();
		Frame = 0;
	}

	if ((PlayerHpOld != PlayerHp) && Frame > 30)
	{
		PlayerHpOld = PlayerHp + ((float)(60 - Frame) / 30) * (tempold - PlayerHp);
	}

	Frame++;
}

void Player_UI::Draw()
{
	//HPバー用のコンスタントバッファ（定数バッファ）にデータを送る
	int hpCB = Master::mpResourceManager->GetConstBuff("Param");
	CB_PARAM_DATA* cb = (CB_PARAM_DATA*)GetBufferShaderConstantBuffer(hpCB);
	cb->hp[0] = PlayerHp;
	cb->hp[1] = PlayerHpOld;
	cb->hp[2] = PlayerMaxHp;
	cb->hp[3] = 0.0f;

	cb->lostColor[0] = 1.0f;
	cb->lostColor[1] = 0.0f;
	cb->lostColor[2] = 0.0f;
	cb->lostColor[3] = 1.0f;

	cb->diffColor[0] = 1.0f;
	cb->diffColor[1] = 1.0f;
	cb->diffColor[2] = 0.0f;
	cb->diffColor[3] = 1.0f;

	cb->baseColor[0] = 0.0f;
	cb->baseColor[1] = 1.0f;
	cb->baseColor[2] = 0.0f;
	cb->baseColor[3] = 1.0f;

	UpdateShaderConstantBuffer(hpCB);

	SetDrawCustomBlendMode(TRUE, DX_BLEND_SRC_COLOR, DX_BLEND_INV_SRC_ALPHA, DX_BLENDOP_ADD, DX_BLEND_SRC_COLOR, DX_BLEND_INV_SRC_ALPHA, DX_BLENDOP_ADD, 255);
	SetUseZBufferFlag(FALSE); //Zバッファ無効

	SetUsePixelShader(LoadShader);
	DrawPolygonIndexed2DToShader(m_vertices, 4, m_indices, 2);

	SetUsePixelShader(-1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(1400, 840, SlotHandle, true);
	DrawGraph(1600, 840, SlotHandle, true);

	auto player = dynamic_cast<Player*>(GetPlayer);
	EquippedItems* equip = player->GetEquippedItems();

	ItemBase* item0 = equip->GetItem(0);
	ItemBase* item1 = equip->GetItem(1);

	if (item0)
	{
		DrawGraph(1530, 890, item0->GetIcon(), true);
	}

	if (item1)
	{
		DrawGraph(1730, 890, item1->GetIcon(), true);
	}

	SetUseZBufferFlag(TRUE); //Zバッファ有効

}

void Player_UI::Finaliza()
{
	DeleteShader(LoadShader);

}