#pragma once
#include "../Haeder/SubScene.h"

class GoalSubScene : public SubScene
{
private:

	//---‰æ‘œ‚Ì“Ç‚İ‚İ---//
	int Goal_Handle;

	//---UI---//
	int GoalX;
	int GoalY;

	//---BGM---//
	int GoalSE;

public:

	GoalSubScene();
	~GoalSubScene();

	void Initaliza() override;
	void Update() override;
	void Draw() override;
	void Finaliza() override;
};