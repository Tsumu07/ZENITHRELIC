#pragma once
#include "../Haeder/SubScene.h"

class StartSubScene : public SubScene
{
public:

	StartSubScene();
	~StartSubScene();
	void Initaliza() override;
	void Update() override;
	void Draw() override;
	void Finaliza() override;
};