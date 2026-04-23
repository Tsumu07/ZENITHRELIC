#include "../Header/StartSubScene.h"

StartSubScene::StartSubScene()
:Objective(-1)
,ObjectiveX(-1)
,ObjectiveY(-1)
{
}

StartSubScene::~StartSubScene()
{
}

void StartSubScene::Initaliza()
{
	m_timer = 120;
	m_isEnd = false;
	ObjectiveX = 0;
	ObjectiveY = 0;

	Objective = LoadGraph("Assets/Objective.png");

}

void StartSubScene::Update()
{
    SubScene::Update();
}

void StartSubScene::Draw()
{

	DrawGraph(ObjectiveX, ObjectiveY, Objective, true);

}

void StartSubScene::Finaliza()
{
	DeleteGraph(Objective);
}
