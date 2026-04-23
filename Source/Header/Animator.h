#pragma once


#include "../Haeder/AnimationClip.h"
#include <map>
#include <string>
#include "BoxModel.h"


class Animator
{
	std::map<std::string, AnimationClip> clips;//アニメーションクリップ
	std::string currentAnimation;	//現在実行中のアニメーション名
	float frame;					//実行中フレーム数
	BoxModel* model;				//変形させるモデルへのポインタ

public:
	Animator();
	virtual ~Animator();

	void AddAnimationClip(std::string tag, AnimationClip& clip);
	void SetAnimation(std::string tag);//実行中のアニメーションを切り替える
	std::string GetAnimation(void);           //実行中のアニメーションの取得
	void SetModel(BoxModel* m);
	DxLibBox* GetBox(std::string tag);

	void Update();
};
