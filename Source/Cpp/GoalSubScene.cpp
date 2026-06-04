#include "../Header/GoalSubScene.h"
#include "../Header/SceneManager.h"
#include "../Master.h"

GoalSubScene::GoalSubScene()
:Goal_Handle(-1)
,GoalX(-1)
,GoalY(-1)
,GoalSE(-1)
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

	Goal_Handle = LoadGraph("Assets/Clear.png");

	GoalX = 535;
	GoalY = 100;
}

void GoalSubScene::Update()
{
	SubScene::Update();

	if (m_timer <= 0)
	{
		Master::GetSceneManager()->ChangeScene(SceneName::GameClearScene);
	}
}

void GoalSubScene::Draw()
{
	DrawGraph(GoalX, GoalY, Goal_Handle, true);
}

void GoalSubScene::Finaliza()
{
	DeleteSoundMem(GoalSE);

	DeleteGraph(Goal_Handle);
}