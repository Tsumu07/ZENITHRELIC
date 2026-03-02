#pragma once
#include "../Haeder/SubScene.h"

class GoalSubScene : public SubScene
{
public:

	GoalSubScene();
	~GoalSubScene();

	void Initaliza() override;
	void Update() override;
	void Draw() override;
	void Finaliza() override;
};