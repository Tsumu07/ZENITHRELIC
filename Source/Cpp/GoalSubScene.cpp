#include "../Haeder/GoalSubScene.h"
#include "../Haeder/SceneManager.h"
#include "../Master.h"

GoalSubScene::GoalSubScene()
{
}

GoalSubScene::~GoalSubScene()
{
}

void GoalSubScene::Initaliza()
{
	m_timer = 120;
	m_isEnd = false;
}

void GoalSubScene::Update()
{
	SubScene::Update();

	if (m_timer <= 0)
	{
		Master::mpSceneManager->ChangeScene(SceneName::GameClearScene);
	}
}

void GoalSubScene::Draw()
{
	LoadGraphScreen(690, 100, "Assets/Clear.png", true);
}

void GoalSubScene::Finaliza()
{
}