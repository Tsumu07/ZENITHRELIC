#include "../Haeder/StartSubScene.h"

StartSubScene::StartSubScene()
{
}

StartSubScene::~StartSubScene()
{
}

void StartSubScene::Initaliza()
{
	m_timer = 120;
	m_isEnd = false;
}

void StartSubScene::Update()
{
    SubScene::Update();
}

void StartSubScene::Draw()
{
    LoadGraphScreen(0, 0, "Assets/Objective.png", true);

}

void StartSubScene::Finaliza()
{
}
