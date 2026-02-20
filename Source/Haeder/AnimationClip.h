#pragma once

#include "../Haeder/Animation.h"

class Animator;//前方宣言


class AnimationClip
{
	std::vector<Animation> animations;//部位ごとのアニメーション
	float endFrame;	//このアニメーションの最終フレーム
	bool loop;		//ループするかしないか

public:
	AnimationClip();
	virtual ~AnimationClip();

	void AddAnimation(Animation& anim);
	void SetEndFrame(float end);
	void SetLoop(bool l);
	float GetEndFrame();
	bool IsLoop();

	void Update(Animator* boss, float frame);
};
