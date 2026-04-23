#pragma once
#include "KeyFrame.h"
#include <vector>
#include <string>

class Animator;//前方宣言（型のプロトタイプ）

class Animation
{
	std::vector<KeyFrame> keys;
	std::string tag;

public:
	Animation();
	virtual ~Animation();

	void AddKeyFrame(KeyFrame key);
	void SetTag(std::string name);

	void Update(Animator* boss, float frame);
};
