
#include "../Haeder/AnimationClip.h"


AnimationClip::AnimationClip()
{
	animations.clear();
	endFrame = 0.0f;
	loop = false;
}

AnimationClip::~AnimationClip()
{
	animations.clear();
}

void AnimationClip::AddAnimation(Animation& anim)
{
	animations.push_back(anim);
}

void AnimationClip::SetEndFrame(float end)
{
	endFrame = end;
}

void AnimationClip::SetLoop(bool l)
{
	loop = l;
}

float AnimationClip::GetEndFrame()
{
	return endFrame;
}

bool AnimationClip::IsLoop()
{
	return loop;
}

void AnimationClip::Update(Animator* boss, float frame)
{
	//登録されている部位のアニメーションをすべて更新する
	for (auto anim : animations)
	{
		anim.Update(boss, frame);
	}
}
