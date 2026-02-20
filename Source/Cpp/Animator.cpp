
#include "../Haeder/Animator.h"


Animator::Animator()
{
	clips.clear();
	currentAnimation.clear();
	frame = 0.0f;
	model = nullptr;
}

Animator::~Animator()
{
	clips.clear();
	currentAnimation.clear();
}

void Animator::AddAnimationClip(std::string tag, AnimationClip& clip)
{
	clips[tag] = clip;
}

void Animator::SetAnimation(std::string tag)
{
	currentAnimation = tag;
}

void Animator::SetModel(BoxModel* m)
{
	model = m;
}

std::string Animator::GetAnimation(void)
{
	return currentAnimation;
}

DxLibBox* Animator::GetBox(std::string tag)
{
	return model->GetBox(tag);
}

void Animator::Update()
{
	clips[currentAnimation].Update(this, frame);

	frame += 1.0f;

	//アニメーションクリップの最大フレーム数を超えてしまっているか
	if (frame > clips[currentAnimation].GetEndFrame())
	{
		//ループするアニメーションならリセットする
		if (clips[currentAnimation].IsLoop())
			frame = 0.0f;
		else//ループしないなら最終フレームで止まる
			frame = clips[currentAnimation].GetEndFrame();
	}
}
