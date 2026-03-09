#include "../Haeder/GoalSubScene.h"
#include "../Haeder/SceneManager.h"
#include "../Master.h"

GoalSubScene::GoalSubScene()
:GoalSE(-1)
{
}

GoalSubScene::~GoalSubScene()
{
}

void GoalSubScene::Initaliza()
{

	m_timer = 120;
	m_isEnd = false;

	GoalSE = LoadSoundMem("Musics/Goal.mp3");

	PlaySoundMem(GoalSE, DX_PLAYTYPE_BACK);
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