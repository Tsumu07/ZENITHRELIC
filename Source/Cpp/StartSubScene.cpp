#include "../Haeder/StartSubScene.h"

StartSubScene::StartSubScene()
{
}

StartSubScene::~StartSubScene()
{
}

void StartSubScene::Initaliza()
{
	m_timer = 180; // 3ïb
	m_isEnd = false;
}

void StartSubScene::Update()
{
}

void StartSubScene::Draw()
{
    // îºìßñæçïîwåi
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawString(500, 300, "ÉSÅ[ÉãÇ…å¸Ç©Ç¶ÅI", GetColor(255, 255, 255));
}

void StartSubScene::Finaliza()
{
}
