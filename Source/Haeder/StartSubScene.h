#pragma once
#include "../Haeder/SubScene.h"

class StartSubScene : public SubScene
{
private:

	//---‰æ‘œ‚Ì“Ç‚İ‚İ---//
	int Objective;

	//---UI--//
	int ObjectiveX;
	int ObjectiveY;

public:

	StartSubScene();
	~StartSubScene();
	void Initaliza() override;
	void Update() override;
	void Draw() override;
	void Finaliza() override;
};